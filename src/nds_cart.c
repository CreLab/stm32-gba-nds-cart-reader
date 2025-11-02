#include <assert.h>
#include <stdbool.h>
#include <stm32f1xx_hal.h>
#include <string.h>

#include "nds_cart.h"
#include "util.h"
#include "gpios.h"

#define NDS_PAGE_SIZE 0x1000
#define NDS_CHUNK_SIZE 0x200
#define NDS_SMALL_HEADER_SIZE 0x200
#define NDS_EXT_HEADER_SIZE 0x1000

__attribute__((always_inline)) static inline void wait_cycles(size_t cycles)
{
#pragma GCC unroll 64
    for (size_t i = 0; i < cycles; i++)
    {
        __asm__ volatile("nop");
    }
}

static void print_chip_id(const s_nds_chip_id *id)
{
    uint8_t bid[4];
    memcpy(bid, id, 4);
    uart_printf("chip_id: %02x %02x %02x %02x\r\n", bid[0], bid[1], bid[2], bid[3]);
}

__attribute__((always_inline)) static inline uint8_t data_in_cycle(size_t cycles)
{
    clk_low();
    wait_cycles(cycles);
    uint8_t ret = data_input();
    clk_high();
    wait_cycles(cycles);
    return ret;
}

__attribute__((always_inline)) static inline void data_out_cycle(uint8_t d, size_t cycles)
{
    clk_low();
    data_output(d);
    wait_cycles(cycles);
    clk_high();
    wait_cycles(cycles);
}

__attribute__((always_inline)) static inline uint8_t data_in_cycle_42(void)
{
    return data_in_cycle(8);
}

__attribute__((always_inline)) static inline uint8_t data_in_cycle_67(void)
{
    return data_in_cycle(5);
}

__attribute__((always_inline)) static inline void data_out_cycle_42(uint8_t d)
{
    data_out_cycle(d, 8);
}

__attribute__((always_inline)) static inline void data_out_cycle_67(uint8_t d)
{
    data_out_cycle(d, 5);
}

enum nds_proto_rev
{
    NDS_PROTO_REV_MROM,
    NDS_PROTO_REV_1TROM_NAND,
};

s_nds_cart_config nds_cart_state;

static s_blowfish_t blowfish_buf = {0};

static void nds_cart_cmd_dummy(void);
static void nds_cart_cmd_main_data_read(uint8_t *data, uint32_t addr);
static void nds_cart_cmd_enable_key1_nds(void);
static void nds_cart_cmd_enable_key2(void);
static void nds_cart_cmd_chip_id_key1(s_nds_chip_id *chip_id);
// static void nds_cart_cmd_invalid(uint8_t *data, size_t len);
static void nds_cart_cmd_get_secure_area(uint8_t *data, size_t page);
static void nds_cart_cmd_chip_id_key2(s_nds_chip_id *chip_id);
static void nds_cart_cmd_enable_data_mode(void);

static void nds_cart_read_header(uint8_t *data, bool extended);
static void nds_cart_read_main_data_page(uint8_t *data, size_t page);
static void nds_cart_read_secure_area_page(uint8_t *data, size_t page);

static void nds_cart_reset(void);

static void key1_init_keycode(uint32_t idcode, uint32_t level, uint32_t modulo, bool dsi);
static void key1_encrypt_64bit(uint32_t *data);
static void key1_decrypt_64bit(uint32_t *data);

static void nds_cart_begin_key1(void)
{
    myassert(nds_cart_state.state == NDS_CART_RAW,
             "cart must be in raw mode before beginning key1\r\n", NULL);

    uint32_t secure_area_disable[2] = {nds_cart_state.secure_area_disable[0],
                                       nds_cart_state.secure_area_disable[1]};

    key1_init_keycode(nds_cart_state.game_code, 1, 8, false);
    key1_decrypt_64bit(secure_area_disable);
    key1_init_keycode(nds_cart_state.game_code, 2, 8, false);

    nds_cart_cmd_enable_key1_nds();

    nds_cart_state.state = NDS_CART_KEY1;

    nds_cart_cmd_enable_key2();

    s_nds_chip_id chip_id;
    nds_cart_cmd_chip_id_key1(&chip_id);

    if (memcmp(&chip_id, &nds_cart_state.chip_id, sizeof(chip_id)))
    {
        DEBUG_PRINT("chip_id with key1 cmd doesn't match initial chip_id:\r\n");
        print_chip_id(&chip_id);
    }
}

static void nds_cart_begin_key2(void)
{
    myassert(nds_cart_state.state == NDS_CART_KEY1,
             "cart must be in key1 mode before beginning key2\r\n", NULL);

    nds_cart_cmd_enable_data_mode();

    nds_cart_state.state = NDS_CART_KEY2;

    s_nds_chip_id chip_id;
    nds_cart_cmd_chip_id_key2(&chip_id);

    if (memcmp(&chip_id, &nds_cart_state.chip_id, sizeof(chip_id)))
    {
        DEBUG_PRINT("chip_id with key2 cmd doesn't match initial chip_id:\r\n");
        print_chip_id(&chip_id);
    }
}

void nds_cart_init(void)
{
    data_dir_input();
    clk_high();
    romcs_high();
    reset_high();
    eepromcs_high();
    MODIFY_REG(GPIOC->CRH, 0xFFFFu, 0x1111u);

    nds_cart_reset();
}

static void nds_cart_change_state(uint8_t state)
{
    if (state == NDS_CART_UNINITIALIZED)
    {
        nds_cart_reset();
    }
    else if (state == NDS_CART_RAW && nds_cart_state.state != NDS_CART_RAW)
    {
        nds_cart_rom_init();
        assert(nds_cart_state.state == NDS_CART_RAW);
    }
    else if (state == NDS_CART_KEY1 && nds_cart_state.state != NDS_CART_KEY1)
    {
        nds_cart_rom_init();
        nds_cart_begin_key1();
        assert(nds_cart_state.state == NDS_CART_KEY1);
    }
    else if (state == NDS_CART_KEY2 && nds_cart_state.state != NDS_CART_KEY2)
    {
        nds_cart_rom_init();
        nds_cart_begin_key1();
        nds_cart_begin_key2();
        assert(nds_cart_state.state == NDS_CART_KEY2);
    }
    else if (state == nds_cart_state.state)
    {
        return;
    }
    else
    {
        myassert(false, "switching to invalid state: 0x%x\r\n", (uint32_t) state);
    }
}

void nds_cart_exec_command(s_nds_cart_config* cfg, uint64_t org_cmd, uint8_t *data, size_t len)
{
    romcs_low();
    data_dir_output();

    e_nds_cart_clk_rate clk_rate;
    bool gap_clk;
    bool key2_result;
    size_t gap1;
    size_t gap2;
    uint64_t cmd;

    if (cfg->state == NDS_CART_KEY1)
    {
        clk_rate = cfg->key1_clk_rate;
        gap_clk = cfg->key1_gap_clk;
        gap1 = cfg->key1_gap1 + cfg->key1_gap2;
        gap2 = cfg->key1_gap2;

        cmd = key1_encrypt_cmd(org_cmd);
        key2_result = true;
    }
    else
    {
        clk_rate = cfg->normal_clk_rate;
        gap_clk = cfg->normal_gap_clk;
        gap1 = cfg->normal_gap1 + cfg->normal_gap2;
        gap2 = cfg->normal_gap2;

        if (cfg->state == NDS_CART_KEY2)
        {
            cmd = key2_encrypt_cmd(&nds_cart_state, org_cmd);
            key2_result = true;
        }
        else
        {
            cmd = org_cmd;
            key2_result = false;
        }
    }

    const uint8_t cmd_data[8] = {
            (uint8_t) (cmd >> 56), (uint8_t) (cmd >> 48), (uint8_t) (cmd >> 40),
            (uint8_t) (cmd >> 32), (uint8_t) (cmd >> 24), (uint8_t) (cmd >> 16),
            (uint8_t) (cmd >> 8),  (uint8_t) (cmd >> 0),
    };

    if (clk_rate == NDS_CART_CLK_6P7_MHZ)
    {
        for (size_t i = 0; i < 8; i++)
        {
            data_out_cycle_67(cmd_data[i]);
        }
    }
    else
    {
        for (size_t i = 0; i < 8; i++)
        {
            data_out_cycle_42(cmd_data[i]);
        }
    }

    data_dir_input();

    if (gap_clk)
    {
        if (clk_rate == NDS_CART_CLK_6P7_MHZ)
        {
            for (size_t i = 0; i < gap1; i++)
                (void) data_in_cycle_67();
        }
        else
        {
            for (size_t i = 0; i < gap1; i++)
                (void) data_in_cycle_42();
        }

        if (key2_result)
            cfg->key2 = key2_xcrypt(cfg->key2, NULL, gap1);
    }
    else
    {
        WAIT(gap1 * 12);
    }

    if (len == 0)
        goto cmdend;

    while (true)
    {
        size_t block_size = len;
        if (block_size > NDS_CHUNK_SIZE)
            block_size = NDS_CHUNK_SIZE;

        if (clk_rate == NDS_CART_CLK_6P7_MHZ)
        {
            for (size_t i = 0; i < block_size; i++)
                data[i] = data_in_cycle_67();
        }
        else
        {
            for (size_t i = 0; i < block_size; i++)
                data[i] = data_in_cycle_42();
        }

        if (key2_result)
            cfg->key2 = key2_xcrypt(cfg->key2, data, block_size);

        data += block_size;
        len -= block_size;

        if (len == 0)
            break;

        if (gap_clk)
        {
            if (clk_rate == NDS_CART_CLK_6P7_MHZ)
            {
                for (size_t i = 0; i < gap2; i++)
                    (void) data_in_cycle_67();
            }
            else
            {
                for (size_t i = 0; i < gap2; i++)
                    (void) data_in_cycle_42();
            }

            if (key2_result)
                cfg->key2 = key2_xcrypt(cfg->key2, NULL, gap2);
        }
        else
        {
            WAIT(gap2 * 12);
        }
    }


cmdend:
    data_dir_input();
    romcs_high();
    WAIT(10);
}

static void nds_cart_cmd_dummy(void)
{
    const uint64_t cmd = 0x9F00000000000000;
    uint8_t dummy_data[0x2000];
    nds_cart_exec_command(&nds_cart_state, cmd, dummy_data, sizeof(dummy_data));
}

static void nds_cart_rom_read_page(uint8_t *read_buffer, size_t page_addr)
{
    page_addr &= ~0xFFFu;

    if (page_addr == 0)
    {
        nds_cart_change_state(NDS_CART_RAW);
        if (nds_cart_state.dsi)
        {
            nds_cart_read_header(read_buffer, true);
            memset(&read_buffer[NDS_SMALL_HEADER_SIZE], 0, NDS_PAGE_SIZE - NDS_EXT_HEADER_SIZE);
        }
        else
        {
            nds_cart_read_header(read_buffer, false);
            memset(&read_buffer[NDS_SMALL_HEADER_SIZE], 0, NDS_PAGE_SIZE - NDS_SMALL_HEADER_SIZE);
        }
    }
    else if (page_addr < 0x4000)
    {
        memset(read_buffer, 0, NDS_PAGE_SIZE);
    }
    else if (page_addr < 0x8000)
    {
        if (nds_cart_state.has_secure_area)
        {
            nds_cart_change_state(NDS_CART_KEY1);
            nds_cart_read_secure_area_page(read_buffer, page_addr >> 12);
        }
        else
        {
            memset(read_buffer, 0, NDS_PAGE_SIZE);
        }
    }
    else
    {
        nds_cart_change_state(NDS_CART_KEY2);
        nds_cart_read_main_data_page(read_buffer, page_addr >> 12);
    }
}

void nds_cart_rom_read(size_t byte_addr, uint8_t *data, size_t len)
{
    uint8_t read_buffer[NDS_PAGE_SIZE];

    while (len > 0)
    {
        size_t page_addr = byte_addr & ~0xFFFu;
        size_t page_index = byte_addr & 0xFFFu;

        size_t read_len = NDS_PAGE_SIZE - page_index;
        if (read_len > len)
            read_len = len;

        nds_cart_rom_read_page(read_buffer, page_addr);
        memcpy(data, &read_buffer[page_index], read_len);
        byte_addr += read_len;
        len -= read_len;
        data += read_len;
    }
}

bool nds_cart_rom_init(void)
{
    nds_cart_reset();

    HAL_Delay(10);

    s_nds_chip_id chip_id;
    s_nds_header header;

    nds_cart_state.state = NDS_CART_RAW;

    nds_cart_cmd_dummy();
    nds_cart_read_header((uint8_t *) &header, false);
    nds_cart_cmd_chip_id((uint8_t *) &chip_id);

    nds_cart_state.chip_id = chip_id;
    nds_cart_state.protocol_rev = chip_id.cart_protocol;
    nds_cart_state.normal_gap_clk = header.gamecart_bus_timing_normal.clk_gap;
    nds_cart_state.normal_clk_rate = header.gamecart_bus_timing_normal.clk_rate;
    nds_cart_state.normal_gap1 = header.gamecart_bus_timing_normal.gap1_len;
    nds_cart_state.normal_gap2 = header.gamecart_bus_timing_normal.gap2_len;
    nds_cart_state.key1_gap_clk = chip_id.cart_protocol == 0 ? true : false;
    nds_cart_state.key1_clk_rate = header.gamecart_bus_timing_key1.clk_rate;
    nds_cart_state.key1_gap1 = header.gamecart_bus_timing_key1.gap1_len;
    nds_cart_state.key1_gap2 = header.gamecart_bus_timing_key1.gap2_len;
    nds_cart_state.key1_delay_ms = (uint16_t) ceil_div(header.secure_area_delay * 1000, 131072);

    if (header.unit_code == 0x0)
    {
        nds_cart_state.nds = true;
        nds_cart_state.dsi = false;
    }
    else if (header.unit_code == 0x2)
    {
        nds_cart_state.nds = true;
        nds_cart_state.dsi = true;
    }
    else if (header.unit_code == 0x3)
    {
        nds_cart_state.nds = false;
        nds_cart_state.dsi = true;
    }
    else
    {
        DEBUG_PRINTF("NDS cart: illegal unit code: %02x", header.unit_code);
        return false;
    }

    if (header.arm9_rom_offset >= 0x8000)
        nds_cart_state.has_secure_area = false;
    else
        nds_cart_state.has_secure_area = true;

    nds_cart_state.game_code = header.game_code_uint;
    nds_cart_state.secure_area_disable[0] = header.secure_area_disable_uint[0];
    nds_cart_state.secure_area_disable[1] = header.secure_area_disable_uint[1];
    nds_cart_state.seed_byte = header.encryption_seed_select;

    nds_cart_state.kkkkk = 0x98bc7;
    nds_cart_state.iii = 0x20C;
    nds_cart_state.jjj = 0xB5B;
    nds_cart_state.llll = 0xd44e;
    nds_cart_state.mmm = 0x733;
    nds_cart_state.nnn = 0xc55;
    nds_cart_state.key2 = key2_init(true);

    return true;
}

static void nds_cart_read_header(uint8_t *data, bool extended)
{
    assert(nds_cart_state.state == NDS_CART_RAW);

    uint64_t cmd = 0x0000000000000000;

    if (extended)
    {
        if (nds_cart_state.protocol_rev == NDS_PROTO_REV_1TROM_NAND)
        {
            for (size_t chunk = 0; chunk < NDS_EXT_HEADER_SIZE / NDS_CHUNK_SIZE; chunk++)
            {
                size_t chunk_addr = chunk * NDS_CHUNK_SIZE;
                cmd |= (uint64_t) chunk_addr << 24;
                nds_cart_exec_command(&nds_cart_state, cmd, &data[chunk_addr], NDS_CHUNK_SIZE);
            }
        }
        else
        {
            nds_cart_exec_command(&nds_cart_state,cmd, data, NDS_EXT_HEADER_SIZE);
        }
    }
    else
    {
        nds_cart_exec_command(&nds_cart_state,cmd, data, NDS_SMALL_HEADER_SIZE);
        for (size_t i = NDS_SMALL_HEADER_SIZE; i < NDS_EXT_HEADER_SIZE; i++)
            data[i] = 0;
    }
}

void nds_cart_cmd_chip_id(uint8_t data[4])
{
    assert(nds_cart_state.state == NDS_CART_RAW);

    const uint64_t cmd = 0x9000000000000000;

    nds_cart_exec_command(&nds_cart_state, cmd, data, 4);
}

static void nds_cart_cmd_main_data_read(uint8_t *data, uint32_t addr)
{
    uint64_t cmd = 0xB700000000000000;
    cmd |= ((uint64_t) addr & 0xFFFFFFFF) << 24;

    nds_cart_exec_command(&nds_cart_state, cmd, data, NDS_CHUNK_SIZE);
}

static void nds_cart_cmd_enable_key1_nds(void)
{
    uint8_t reply[1];
    uint64_t cmd = 0x3C00000000000000;
    cmd |= (uint64_t) (nds_cart_state.iii & 0xFFF) << 44;
    cmd |= (uint64_t) (nds_cart_state.jjj & 0xFFF) << 32;
    cmd |= (uint64_t) (nds_cart_state.kkkkk & 0xFFFFF) << 8;
    nds_cart_exec_command(&nds_cart_state, cmd, reply, 0);
}

static void nds_cart_cmd_enable_key2(void)
{
    assert(nds_cart_state.state == NDS_CART_KEY1);

    uint8_t reply[1];
    uint64_t cmd = 0x4000000000000000;
    cmd |= (uint64_t) (nds_cart_state.llll & 0xFFFF) << 44;
    cmd |= (uint64_t) (nds_cart_state.mmm & 0xFFF) << 32;
    cmd |= (uint64_t) (nds_cart_state.nnn & 0xFFF) << 20;
    cmd |= (uint64_t) (nds_cart_state.kkkkk & 0xFFFFF) << 0;

    assert(cmd == key1_decrypt_cmd(key1_encrypt_cmd(cmd)));

    if (nds_cart_state.protocol_rev == NDS_PROTO_REV_MROM)
    {
        HAL_Delay(nds_cart_state.key1_delay_ms);
        nds_cart_exec_command(&nds_cart_state, cmd, reply, 0);
        nds_cart_state.key2 = key2_init(false);
    }
    else
    {
        nds_cart_exec_command(&nds_cart_state, cmd, reply, 0);
        HAL_Delay(nds_cart_state.key1_delay_ms);
        nds_cart_state.key2 = key2_init(false);
        nds_cart_exec_command(&nds_cart_state, cmd, reply, 0);
    }

    nds_cart_state.kkkkk += 1;
}

static void nds_cart_cmd_chip_id_key1(s_nds_chip_id *chip_id)
{
    assert(nds_cart_state.state == NDS_CART_KEY1);

    uint64_t cmd = 0x1000000000000000;
    cmd |= (uint64_t) (nds_cart_state.llll & 0xFFFF) << 44;
    cmd |= (uint64_t) (nds_cart_state.iii & 0xFFF) << 32;
    cmd |= (uint64_t) (nds_cart_state.jjj & 0xFFF) << 20;
    cmd |= (uint64_t) (nds_cart_state.kkkkk & 0xFFFFF) << 0;

    if (nds_cart_state.protocol_rev == NDS_PROTO_REV_MROM)
    {
        HAL_Delay(nds_cart_state.key1_delay_ms);
        nds_cart_exec_command(&nds_cart_state, cmd, (uint8_t *) chip_id, sizeof(*chip_id));
    }
    else
    {
        nds_cart_exec_command(&nds_cart_state, cmd, (uint8_t *) chip_id, 0);
        HAL_Delay(nds_cart_state.key1_delay_ms);
        nds_cart_exec_command(&nds_cart_state, cmd, (uint8_t *) chip_id, sizeof(*chip_id));
    }

    nds_cart_state.kkkkk += 1;
}

static void nds_cart_cmd_get_secure_area(uint8_t *data, size_t page)
{
    assert(nds_cart_state.state == NDS_CART_KEY1);


    uint64_t cmd = 0x2000000000000000;
    cmd |= (uint64_t) (page & 0xFFFF) << 44;
    cmd |= (uint64_t) (nds_cart_state.iii & 0xFFF) << 32;
    cmd |= (uint64_t) (nds_cart_state.jjj & 0xFFF) << 20;
    cmd |= (uint64_t) (nds_cart_state.kkkkk & 0xFFFFF) << 0;

    if (nds_cart_state.protocol_rev == NDS_PROTO_REV_MROM)
    {
        HAL_Delay(nds_cart_state.key1_delay_ms);
        nds_cart_exec_command(&nds_cart_state, cmd, data, NDS_PAGE_SIZE);
    }
    else
    {
        nds_cart_exec_command(&nds_cart_state, cmd, data, 0);
        HAL_Delay(nds_cart_state.key1_delay_ms);
        for (size_t i = 0; i < NDS_PAGE_SIZE / NDS_CHUNK_SIZE; i++)
        {
            nds_cart_exec_command(&nds_cart_state, cmd, data, NDS_CHUNK_SIZE);
            data += NDS_CHUNK_SIZE;
        }
    }

    nds_cart_state.kkkkk += 1;
}

static void nds_cart_cmd_enable_data_mode(void)
{
    assert(nds_cart_state.state == NDS_CART_KEY1);

    uint8_t reply[1];
    uint64_t cmd = 0xA000000000000000;
    cmd |= (uint64_t) (nds_cart_state.llll & 0xFFFF) << 44;
    cmd |= (uint64_t) (nds_cart_state.iii & 0xFFF) << 32;
    cmd |= (uint64_t) (nds_cart_state.jjj & 0xFFF) << 20;
    cmd |= (uint64_t) (nds_cart_state.kkkkk & 0xFFFFF) << 0;

    if (nds_cart_state.protocol_rev == NDS_PROTO_REV_MROM)
    {
        HAL_Delay(nds_cart_state.key1_delay_ms);
        nds_cart_exec_command(&nds_cart_state, cmd, reply, 0);
    }
    else
    {
        nds_cart_exec_command(&nds_cart_state, cmd, reply, 0);
        HAL_Delay(nds_cart_state.key1_delay_ms);
        nds_cart_exec_command(&nds_cart_state, cmd, reply, 0);
    }

    nds_cart_state.kkkkk += 1;
}

static void nds_cart_cmd_chip_id_key2(s_nds_chip_id *chip_id)
{
    assert(nds_cart_state.state == NDS_CART_KEY2);

    const uint64_t cmd = 0xB800000000000000;
    nds_cart_exec_command(&nds_cart_state, cmd, (uint8_t *) chip_id, sizeof(*chip_id));
}

static void nds_cart_read_main_data_page(uint8_t *data, size_t page)
{
    assert(nds_cart_state.state == NDS_CART_KEY2);

    for (size_t chunk = 0; chunk < NDS_PAGE_SIZE / NDS_CHUNK_SIZE; chunk++)
    {
        uint32_t addr = (page << 12) + chunk * NDS_CHUNK_SIZE;
        nds_cart_cmd_main_data_read(data, addr);
        data += NDS_CHUNK_SIZE;
    }
}

static void nds_cart_read_secure_area_page(uint8_t *data, size_t page)
{
    // TODO secure are delay
    assert(nds_cart_state.state == NDS_CART_KEY1);
    assert(page >= 4 && page <= 7);

    union
    {
        uint8_t _u8[NDS_PAGE_SIZE];
        uint32_t _u32[NDS_PAGE_SIZE / 4];
    } secure_area_page;

    nds_cart_cmd_get_secure_area(secure_area_page._u8, page);

    if (page == 4)
    {
        key1_decrypt_64bit(&secure_area_page._u32[0]);
        key1_init_keycode(nds_cart_state.game_code, 3, 8, false);
        const size_t SEC_AREA_KEY1_CRYPT_LEN = 0x800;
        for (size_t i = 0; i < SEC_AREA_KEY1_CRYPT_LEN / sizeof(uint32_t); i += 2)
            key1_decrypt_64bit(&secure_area_page._u32[i]);

        if (memcmp(secure_area_page._u8, "encryObj", 8))
        {
            DEBUG_PRINT("ERROR: secure area not correctly decrypted:");
            for (size_t i = 0; i < 8; i++)
                DEBUG_PRINTF(" %02x", secure_area_page._u8[i]);
            DEBUG_PRINT("\r\n");
        }
        else
        {
            secure_area_page._u32[0] = 0xE7FFDEFF;
            secure_area_page._u32[1] = 0xE7FFDEFF;
        }

        key1_init_keycode(nds_cart_state.game_code, 2, 8, false);
    }

    memcpy(data, secure_area_page._u8, sizeof(secure_area_page._u8));
}

static void nds_cart_reset(void)
{
    reset_low();
    HAL_Delay(10);
    reset_high();

    nds_cart_state.state = NDS_CART_UNINITIALIZED;
    nds_cart_state.normal_gap_clk = false;
    nds_cart_state.key1_gap_clk = false;
    nds_cart_state.normal_clk_rate = false;
    nds_cart_state.key1_clk_rate = false;
    nds_cart_state.nds = true;
    nds_cart_state.dsi = false;
    nds_cart_state.has_secure_area = true;
    nds_cart_state.normal_gap1 = 0x8F8;
    nds_cart_state.key1_gap1 = 0x8F8;
    nds_cart_state.normal_gap2 = 0x18;
    nds_cart_state.key1_gap2 = 0x18;
}

static void key1_encrypt_64bit(uint32_t *data)
{
    uint32_t y = data[0];
    uint32_t x = data[1];

    for (int i = 0; i <= 15; i++)
    {
        uint32_t z = blowfish_buf.P[i] ^ x;
        x = blowfish_buf.S[0][(z >> 24) & 0xFF];
        x = blowfish_buf.S[1][(z >> 16) & 0xFF] + x;
        x = blowfish_buf.S[2][(z >> 8) & 0xFF] ^ x;
        x = blowfish_buf.S[3][(z >> 0) & 0xFF] + x;
        x = y ^ x;
        y = z;
    }

    data[0] = x ^ blowfish_buf.P[16];
    data[1] = y ^ blowfish_buf.P[17];
}

static void key1_decrypt_64bit(uint32_t *data)
{
    uint32_t y = data[0];
    uint32_t x = data[1];

    for (int i = 17; i >= 2; i--)
    {
        uint32_t z = blowfish_buf.P[i] ^ x;
        x = blowfish_buf.S[0][(z >> 24) & 0xFF];
        x = blowfish_buf.S[1][(z >> 16) & 0xFF] + x;
        x = blowfish_buf.S[2][(z >> 8) & 0xFF] ^ x;
        x = blowfish_buf.S[3][(z >> 0) & 0xFF] + x;
        x = y ^ x;
        y = z;
    }

    data[0] = x ^ blowfish_buf.P[1];
    data[1] = y ^ blowfish_buf.P[0];
}

uint64_t key1_encrypt_cmd(uint64_t cmd)
{
    union
    {
        uint32_t _u32[2];
        uint64_t _u64;
    } u;

    u._u64 = cmd;
    key1_encrypt_64bit(u._u32);
    return u._u64;
}

uint64_t key1_decrypt_cmd(uint64_t cmd)
{
    union
    {
        uint32_t _u32[2];
        uint64_t _u64;
    } u;

    u._u64 = cmd;
    key1_decrypt_64bit(u._u32);
    return u._u64;
}

static void key1_apply_keycode(uint32_t *keycode, uint32_t modulo)
{
    uint32_t scratch[2];
    scratch[0] = scratch[1] = 0;

    key1_encrypt_64bit(&keycode[1]);
    key1_encrypt_64bit(&keycode[0]);

    for (uint32_t i = 0; i < 18; i++)
    {
        blowfish_buf.P[i] ^= __builtin_bswap32(keycode[i % (modulo / 4u)]);
    }

    for (uint32_t i = 0; i < 18; i += 2)
    {
        key1_encrypt_64bit(scratch);
        blowfish_buf.P[i + 0] = scratch[1];
        blowfish_buf.P[i + 1] = scratch[0];
    }

    for (uint32_t i = 0; i < 4; i++)
    {
        for (uint32_t j = 0; j < 256; j += 2)
        {
            key1_encrypt_64bit(scratch);
            blowfish_buf.S[i][j + 0] = scratch[1];
            blowfish_buf.S[i][j + 1] = scratch[0];
        }
    }
}

static void key1_init_keycode(uint32_t idcode, uint32_t level, uint32_t modulo, bool dsi)
{
    uint32_t keycode[3];

    if (dsi)
        memcpy(&blowfish_buf, dsi_cart_key, sizeof(blowfish_buf));
    else
        memcpy(&blowfish_buf, nds_cart_key, sizeof(blowfish_buf));

    keycode[0] = idcode;
    keycode[1] = idcode / 2;
    keycode[2] = idcode * 2;

    if (level >= 1)
        key1_apply_keycode(keycode, modulo);
    if (level >= 2)
        key1_apply_keycode(keycode, modulo);

    keycode[1] *= 2;
    keycode[2] /= 2;

    if (level >= 3)
        key1_apply_keycode(keycode, modulo);
}

s_key2 key2_init(bool hw_reset)
{
    s_key2 key = {0};

    uint64_t seed0 = 0x58C56DE0E8;
    uint64_t seed1 = 0x5C879B9B05;

    if (!hw_reset)
    {
        const uint64_t mmm = (uint64_t) (nds_cart_state.mmm & 0xFFF) << 27;
        const uint64_t nnn = (uint64_t) (nds_cart_state.nnn & 0xFFF) << 15;
        static const uint8_t seedbytes[8] = {0xE8, 0x4D, 0x5A, 0xB1, 0x17, 0x8F, 0x99, 0xD5};

        seed0 = (mmm | nnn) + 0x6000 + seedbytes[nds_cart_state.seed_byte % 8];
    }

    key.x = bitrev_64(seed0) >> (64 - 39);
    key.y = bitrev_64(seed1) >> (64 - 39);

    return key;
}

s_key2 key2_xcrypt(s_key2 key2, uint8_t *data, size_t len)
{
    s_key2 key = {0};
            
    uint64_t x = key2.x;
    uint64_t y = key2.y;

    if (data)
    {
        for (size_t i = 0; i < len; i++)
        {
            x = (((x >> 5) ^ (x >> 17) ^ (x >> 18) ^ (x >> 31)) & 0xFF) + (x << 8);
            x &= 0x7FFFFFFFFF;
            y = (((y >> 5) ^ (y >> 23) ^ (y >> 18) ^ (y >> 31)) & 0xFF) + (y << 8);
            y &= 0x7FFFFFFFFF;
            data[i] = (uint8_t) (data[i] ^ x ^ y);
        }
    }
    else
    {
        for (size_t i = 0; i < len; i++)
        {
            x = (((x >> 5) ^ (x >> 17) ^ (x >> 18) ^ (x >> 31)) & 0xFF) + (x << 8);
            x &= 0x7FFFFFFFFF;
            y = (((y >> 5) ^ (y >> 23) ^ (y >> 18) ^ (y >> 31)) & 0xFF) + (y << 8);
            y &= 0x7FFFFFFFFF;
        }
    }

    key.x = x;
    key.y = y;
    
    return key;
}

uint64_t key2_encrypt_cmd(s_nds_cart_config * cfg, uint64_t cmd)
{
    uint8_t cmd_data[8];

#pragma GCC unroll 8
    for (size_t i = 0; i < 8; i++)
    {
        cmd_data[i] = (uint8_t) (cmd >> 56);
        cmd <<= 8;
    }

    cfg->key2 = key2_xcrypt(cfg->key2, cmd_data, sizeof(cmd_data));

    cmd = 0;
#pragma GCC unroll 8
    for (size_t i = 0; i < 8; i++)
    {
        cmd <<= 8;
        cmd |= cmd_data[i];
    }

    return cmd;
}
