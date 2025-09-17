#include "gba_cart.h"
#include "hw_config.h"

static bool gba_cart_get_eeprom_type(void);
static void gba_cart_eeprom_read_data(uint16_t block_addr, uint8_t *data, bool large);
static bool gba_cart_eeprom_write_data(uint16_t block_addr, const uint8_t *data, bool large);

static size_t gba_cart_delay = 2;
#define LVL_SHIFT_DELAY()                                                                          \
    do                                                                                             \
    {                                                                                              \
        WAIT(0);                                                                                   \
    }                                                                                              \
    while (0)
#define GBA_CART_DELAY()                                                                           \
    do                                                                                             \
    {                                                                                              \
        WAIT(gba_cart_delay);                                                                      \
    }                                                                                              \
    while (0)

__STATIC_FORCEINLINE void adbus_dir_input(void)
{
    configDataLanesAsInput(GPIOB, E_PIN_GROUP_0_7);
    configDataLanesAsInput(GPIOB, E_PIN_GROUP_8_15);
    ADBUS_LEVEL_DIR_INPUT();
    LVL_SHIFT_DELAY();
}

__STATIC_FORCEINLINE void adbus_dir_output(uint16_t init_value)
{
    ADBUS_LEVEL_DIR_OUTPUT();
    LVL_SHIFT_DELAY();
    GPIOB->ODR = init_value;
    configDataLanesAsOutput(GPIOB, E_PIN_GROUP_0_7);
    configDataLanesAsOutput(GPIOB, E_PIN_GROUP_8_15);
    GBA_CART_DELAY();
}

__STATIC_FORCEINLINE void uabus_dir_input(void)
{
    configDataLanesAsInput(GPIOA, E_PIN_GROUP_0_7);
    UABUS_LEVEL_DIR_INPUT();
    LVL_SHIFT_DELAY();
}

__STATIC_FORCEINLINE void uabus_dir_output(uint8_t init_value)
{
    UABUS_LEVEL_DIR_OUTPUT();
    LVL_SHIFT_DELAY();
    uint8_t ninit_value = (uint8_t) ~init_value;
    GPIOA->BSRR = (uint32_t) (init_value | (ninit_value << 16));
    configDataLanesAsOutput(GPIOA, E_PIN_GROUP_0_7);
    GBA_CART_DELAY();
}

void gba_cart_init(void)
{
    adbus_dir_input();

    ADBUS_LEVEL_DIR_INPUT();

    MODIFY_REG(GPIOD->CRL, 0xF00u, 0x100u);

    UABUS_LEVEL_DIR_INPUT();

    MODIFY_REG(GPIOC->CRH, 0xF0000u, 0x10000u);

    NCS_HIGH();
    NCS2_HIGH();
    NRD_HIGH();
    NWR_HIGH();

    MODIFY_REG(GPIOA->CRH, 0xFFF0000Fu, 0x11100001u);
    uabus_dir_input();
}

void gba_cart_test(void)
{

}

size_t gba_cart_rom_size()
{
    for (uint32_t i = 19; i < 24; i++)
    {
        uint32_t base_addr = 1u << i;
        uint32_t errors = 0;

        for (uint32_t j = 0; j < 1024; j++)
        {
            uint16_t v;
            gba_cart_rom_read(base_addr + j, &v, 1);
            if (v != j)
                errors++;
        }

        if (errors < 4)
            return base_addr << 1;
    }
    return 0x2000000;
}

size_t gba_cart_save_size()
{
    static const uint32_t BLOCK_SIZE = 512;
    uint32_t buffer[BLOCK_SIZE];
    for (uint32_t i = 0; i < 0x2000000; i += (BLOCK_SIZE * 4))
    {
        gba_cart_rom_read(i / 2, (uint16_t *) buffer, BLOCK_SIZE * 2);
        for (uint32_t j = 0; j < BLOCK_SIZE; j++)
        {
            if (buffer[j] == *(uint32_t *) "EEPR")
            {
                uint32_t cmp;
                if (j + 1 == BLOCK_SIZE)
                    gba_cart_rom_read((i / 2) + (j * 2), (uint16_t *) &cmp, 2);
                else
                    cmp = buffer[j + 1];
                if ((cmp & 0xFFFFFF) == ((*(uint32_t *) "OM_") & 0xFFFFFF))
                {
                    if (gba_cart_get_eeprom_type())
                        return 0x2000;
                    else
                        return 0x200;
                }
            }
            else if (buffer[j] == *(uint32_t *) "FLAS")
            {
                uint32_t cmp;
                if (j + 1 == BLOCK_SIZE)
                    gba_cart_rom_read((i / 2) + (j * 2), (uint16_t *) &cmp, 2);
                else
                    cmp = buffer[j + 1];

                char tmp[4] = "H_";
                uint32_t *ptmp = (uint32_t *) tmp;

                if (cmp == *(uint32_t *) "H1M_")
                {
                    return 0x20000;
                }
                else if ((cmp & 0xFFFF) == (ptmp[0] & 0xFFFF))
                {
                    return 0x10000;
                }
            }
            else if (buffer[j] == *(uint32_t *) "SRAM")
            {
                uint32_t cmp;
                if (j + 1 == BLOCK_SIZE)
                    gba_cart_rom_read((i / 2) + (j * 2), (uint16_t *) &cmp, 2);
                else
                    cmp = buffer[j + 1];

                char tmp[4] = "_";
                uint32_t *ptmp = (uint32_t *) tmp;

                if ((cmp & 0xFF) == (ptmp[0] & 0xFF))
                {
                    return 0x8000;
                }
            }
        }
    }
    return 0u;
}

void gba_cart_rom_read(uint32_t word_addr, uint16_t *data, size_t len)
{
    adbus_dir_output((uint16_t) (word_addr & 0xFFFF));
    uint8_t word_addr_msb = (uint8_t) ((word_addr >> 16) & 0xFF);
    uabus_dir_output(word_addr_msb);

    NCS_LOW();

    adbus_dir_input();

    while (len-- > 0)
    {
        NRD_LOW();

        *data++ = (uint16_t) GPIOB->IDR;
        word_addr += 1;

        NRD_HIGH();

        if (word_addr >> 16 != word_addr_msb)
        {
            word_addr_msb = (uint8_t) ((word_addr >> 16) & 0xFF);
            NCS_HIGH();
            uabus_dir_output(word_addr_msb);
            NCS_LOW();
        }
    }

    NCS_HIGH();
    uabus_dir_input();
}

uint16_t gba_cart_rom_read_word(uint32_t word_addr)
{
    uint16_t retval;
    gba_cart_rom_read(word_addr, &retval, 1);
    return retval;
}

void gba_cart_rom_write(uint32_t word_addr, const uint16_t *data, size_t len)
{
    adbus_dir_output((uint16_t) (word_addr & 0xFFFF));
    uint8_t word_addr_msb = (uint8_t) ((word_addr >> 16) & 0xFF);
    uabus_dir_output(word_addr_msb);

    NCS_LOW();

    while (len-- > 0)
    {
        adbus_dir_output(*data++);
        NWR_LOW();
        NWR_HIGH();
        word_addr += 1;

        if (word_addr >> 16 != word_addr_msb)
        {
            word_addr_msb = (uint8_t) ((word_addr >> 16) & 0xFF);
            NCS_HIGH();
            uabus_dir_output(word_addr_msb);
            NCS_LOW();
        }
    }

    NCS_HIGH();
    adbus_dir_input();
    uabus_dir_input();
}

void gba_cart_rom_write_word(uint32_t word_addr, uint16_t data)
{
    gba_cart_rom_write(word_addr, &data, 1);
}

void gba_cart_sram_read(uint16_t byte_addr, uint8_t *data, size_t len)
{
    while (len-- > 0)
    {
        adbus_dir_output(byte_addr++);
        NCS2_LOW();
        NRD_LOW();
        *data++ = (uint8_t) GPIOA->IDR;
        NRD_HIGH();
        NCS2_HIGH();
    }

    adbus_dir_input();
}

uint8_t gba_cart_sram_read_byte(uint16_t byte_addr)
{
    uint8_t retval;
    gba_cart_sram_read(byte_addr, &retval, 1);
    return retval;
}

void gba_cart_sram_write(uint16_t byte_addr, const uint8_t *data, size_t len)
{
    while (len-- > 0)
    {
        adbus_dir_output(byte_addr++);
        NCS2_LOW();
        uabus_dir_output(*data++);
        NWR_LOW();
        NWR_HIGH();
        NCS2_HIGH();
    }

    adbus_dir_input();
    uabus_dir_input();
}

void gba_cart_sram_write_byte(uint16_t byte_addr, uint8_t data)
{
    gba_cart_sram_write(byte_addr, &data, 1);
}

bool gba_cart_flash_erase(void)
{
    gba_cart_sram_write_byte(0x5555, 0xAA);
    gba_cart_sram_write_byte(0x2AAA, 0x55);
    gba_cart_sram_write_byte(0x5555, 0x80);
    gba_cart_sram_write_byte(0x5555, 0xAA);
    gba_cart_sram_write_byte(0x2AAA, 0x55);
    gba_cart_sram_write_byte(0x5555, 0x10);

    uint32_t timeout_start = HAL_GetTick();
    while (gba_cart_sram_read_byte(0x0) != 0xFF)
    {
        if (HAL_GetTick() >= timeout_start + 2000)
            return false;
    }
    return true;
}

bool gba_cart_flash_write(uint16_t byte_addr, uint8_t *data, size_t len)
{
    while (len-- > 0)
    {
        gba_cart_sram_write_byte(0x5555, 0xAA);
        gba_cart_sram_write_byte(0x2AAA, 0x55);
        gba_cart_sram_write_byte(0x5555, 0xA0);
        gba_cart_sram_write_byte(byte_addr, *data);

        uint32_t timeout_start = HAL_GetTick();
        while (gba_cart_sram_read_byte(byte_addr) != *data)
        {
            if (HAL_GetTick() >= timeout_start + 1000)
                return false;
        }
        byte_addr++;
        data++;
    }
    return true;
}

void gba_cart_flash_switch_bank(uint8_t bank)
{
    gba_cart_sram_write_byte(0x5555, 0xAA);
    gba_cart_sram_write_byte(0x2AAA, 0x55);
    gba_cart_sram_write_byte(0x5555, 0xB0);
    gba_cart_sram_write_byte(0x0, bank);
}

void gba_cart_eeprom_512_read_data(uint16_t block_addr, uint8_t *data)
{
    gba_cart_eeprom_read_data(block_addr, data, false);
}

bool gba_cart_eeprom_512_write_data(uint16_t block_addr, const uint8_t *data)
{
    return gba_cart_eeprom_write_data(block_addr, data, false);
}

void gba_cart_eeprom_8k_read_data(uint16_t block_addr, uint8_t *data)
{
    gba_cart_eeprom_read_data(block_addr, data, true);
}

bool gba_cart_eeprom_8k_write_data(uint16_t block_addr, const uint8_t *data)
{
    return gba_cart_eeprom_write_data(block_addr, data, true);
}

static bool gba_cart_get_eeprom_type(void)
{
    static const int NBLK = 96;
    uint8_t buffer[NBLK * 8];

    for (int i = 0; i < NBLK; i++)
    {
        gba_cart_eeprom_8k_read_data((uint16_t) i, &buffer[i * 8]);
    }

    uint8_t ref = buffer[0];

    for (int i = 8; i < (NBLK * 8); i += 8)
    {
        if (buffer[i] != ref)
            return true;
    }

    for (int i = 1; i < (64 * 8); i += 1)
    {
        if (buffer[i] != ref)
            return false;
    }

    for (int i = 0; i < 8; i++)
    {
        buffer[i] = (uint8_t) (i * 0x11);
    }

    gba_cart_eeprom_8k_write_data(0, buffer);
    gba_cart_eeprom_8k_read_data(0, &buffer[0]);
    gba_cart_eeprom_8k_read_data(1, &buffer[1]);

    for (int i = 8; i < 16; i++)
    {
        if (buffer[i] != ref)
        {
            for (int j = 0; j < 64; j++)
            {
                gba_cart_eeprom_512_write_data((uint16_t) j, &buffer[j * 8 + 8]);
            }
            return false;
        }
    }

    gba_cart_eeprom_8k_write_data(0, &buffer[8]);

    return true;
}

static void gba_cart_eeprom_read_data(uint16_t block_addr, uint8_t *data, bool large)
{
    size_t gba_cart_delay_save = gba_cart_delay;
    gba_cart_delay = 8;
    {
        int address_bits = large ? 14 : 6;
        int bitstream_len = 2 + address_bits + 1;
        uint16_t bitstream[bitstream_len];
        bitstream[0] = 1;
        bitstream[1] = 1;
        for (int i = address_bits - 1, j = 0; i >= 0; i--, j++)
        {
            bitstream[2 + j] = (uint16_t) ((block_addr >> i) & 1);
        }
        bitstream[2 + address_bits] = 0;
        gba_cart_rom_write(EEPROM_WORD_ADDR, bitstream, (size_t) bitstream_len);
    }
    {
        size_t bitstream_len = 4 + 64;
        uint16_t bitstream[bitstream_len];
        gba_cart_rom_read(EEPROM_WORD_ADDR, bitstream, bitstream_len);

        for (size_t i = 0; i < 64; i += 8)
        {
            int val = ((bitstream[4 + i + 0] & 1) << 7) | ((bitstream[4 + i + 1] & 1) << 6) |
                      ((bitstream[4 + i + 2] & 1) << 5) | ((bitstream[4 + i + 3] & 1) << 4) |
                      ((bitstream[4 + i + 4] & 1) << 3) | ((bitstream[4 + i + 5] & 1) << 2) |
                      ((bitstream[4 + i + 6] & 1) << 1) | ((bitstream[4 + i + 7] & 1) << 0);
            data[i >> 3] = (uint8_t) val;
        }
    }
    gba_cart_delay = gba_cart_delay_save;
}

static bool gba_cart_eeprom_write_data(uint16_t block_addr, const uint8_t *data, bool large)
{
    size_t gba_cart_delay_save = gba_cart_delay;
    gba_cart_delay = 8;

    int address_bits = large ? 14 : 6;
    int bitstream_len = 2 + address_bits + 64 + 1;
    uint16_t bitstream[bitstream_len];
    bitstream[0] = 1;
    bitstream[1] = 0;

    for (int i = address_bits - 1, j = 0; i >= 0; i--, j++)
    {
        bitstream[2 + j] = (uint16_t) ((block_addr >> i) & 1);
    }

    for (int i = 0; i < 64; i += 8)
    {
        uint8_t d = data[i >> 3];
        bitstream[2 + address_bits + i + 0] = (d >> 7) & 1;
        bitstream[2 + address_bits + i + 1] = (d >> 6) & 1;
        bitstream[2 + address_bits + i + 2] = (d >> 5) & 1;
        bitstream[2 + address_bits + i + 3] = (d >> 4) & 1;
        bitstream[2 + address_bits + i + 4] = (d >> 3) & 1;
        bitstream[2 + address_bits + i + 5] = (d >> 2) & 1;
        bitstream[2 + address_bits + i + 6] = (d >> 1) & 1;
        bitstream[2 + address_bits + i + 7] = (d >> 0) & 1;
    }

    bitstream[2 + address_bits + 64] = 0;

    gba_cart_rom_write(EEPROM_WORD_ADDR, bitstream, (size_t) bitstream_len);

    uint32_t timeout_begin = HAL_GetTick();
    while ((gba_cart_rom_read_word(EEPROM_WORD_ADDR) & 1) != 1)
    {
        if (HAL_GetTick() >= timeout_begin + 10)
        {
            gba_cart_delay = gba_cart_delay_save;
            return false;
        }
    }
    gba_cart_delay = gba_cart_delay_save;
    return true;
}
