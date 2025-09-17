#include "host_interface.h"
#include "gba_cart.h"
#include "nds_cart.h"

typedef struct s_gbaAddr_t
{
    size_t rom_word_addr;
    uint16_t sram_byte_addr;
    uint16_t eeprom_block_addr;
} s_gbaAddr_t;

typedef struct s_ndsAddr_t
{
    size_t rom_byte_addr;
} s_ndsAddr_t;

typedef struct s_host_request_t
{
    uint16_t magic;
    uint16_t type;
    uint16_t id;
    uint16_t len;
    uint8_t data[XFER_MAX_PAYLOAD_SIZE];
} s_host_request_t;

typedef s_host_request_t s_device_reply_t;

#define REQ_BUF_SIZE sizeof(s_host_request_t)
#define REPL_BUF_SIZE sizeof(s_device_reply_t)

static volatile bool isHostRequestAReady = false;
static volatile bool isHostRequestBReady = false;

static s_host_request_t sHostRequestA;
static s_host_request_t sHostRequestB;
static s_device_reply_t sDeviceReply;

s_gbaAddr_t gba = {
        .rom_word_addr = 0,
        .sram_byte_addr = 0,
        .eeprom_block_addr = 0,
};

s_ndsAddr_t nds = {
        .rom_byte_addr = 0,
};

static uint16_t hostInterface_checkPayloadSize(uint16_t length);
static GLOBAL_STATUS hostInterface_checkRequestPackageLength(const s_host_request_t *rq,
                                                             s_device_reply_t *rp, uint16_t length,
                                                             const char *msg);
static GLOBAL_STATUS hostInterface_handle_request(s_host_request_t *rq, s_device_reply_t *rp);
static GLOBAL_STATUS hostInterface_send_reply(void);
static void hostInterface_reply_err(s_device_reply_t *rp, const char *msg, ...);

GLOBAL_STATUS hostInterface_run(void)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    if (isHostRequestAReady)
    {
        CHECK_GLOBAL_STATUS(hostInterface_handle_request(&sHostRequestA, &sDeviceReply));
        isHostRequestAReady = false;
    }
    else if (isHostRequestBReady)
    {
        CHECK_GLOBAL_STATUS(hostInterface_handle_request(&sHostRequestB, &sDeviceReply));
        isHostRequestBReady = false;
    }

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS hostInterface_data_receive(const uint8_t *data, uint16_t size)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    static uint8_t request_receive_buffer[REQ_BUF_SIZE];
    static const s_host_request_t *request_receive = (s_host_request_t *) request_receive_buffer;
    static uint16_t request_receive_pos = 0;
    static bool buffer_overflow = false;

    if (size == 0)
    {
        CHECK_GLOBAL_STATUS(ERROR_STATE_SIZE_INVALID);
    }

    if (buffer_overflow)
    {
        request_receive_pos = 0;
        buffer_overflow = false;
    }

    if (request_receive_pos >= REQ_BUF_SIZE)
    {
        buffer_overflow = true;
        CHECK_GLOBAL_STATUS(ERROR_STATE_BUFFER_OVERFLOW);
    }

    if ((size_t) size + request_receive_pos > REQ_BUF_SIZE)
    {
        size = (uint16_t) (REQ_BUF_SIZE - request_receive_pos);
    }

    memcpy(request_receive_buffer + request_receive_pos, data, size);
    request_receive_pos = (uint16_t) (request_receive_pos + size);

    if (request_receive_pos < offsetof(s_device_reply_t, magic) + sizeof(uint16_t))
    {
        CHECK_GLOBAL_STATUS(ERROR_STATE_POS_MISMATCH);
    }

    while (request_receive->magic != HOST_REQ_MAGIC)
    {
        memmove(&request_receive_buffer[0], &request_receive_buffer[1],
                (size_t) (request_receive_pos - 1));
        request_receive_pos--;
        if (request_receive_pos <= 1)
        {
            CHECK_GLOBAL_STATUS(ERROR_STATE_OK);
        }
    }

    if (request_receive_pos < offsetof(s_device_reply_t, len) + sizeof(uint16_t))
    {
        CHECK_GLOBAL_STATUS(ERROR_STATE_POS_MISMATCH);
    }

    uint16_t packet_len = request_receive->len;
    if (request_receive_pos < packet_len + sizeof(s_host_request_t))
    {
        CHECK_GLOBAL_STATUS(ERROR_STATE_POS_MISMATCH);
    }

    if (isHostRequestAReady == false)
    {
        size_t bytes_to_copy = sizeof(s_host_request_t) + packet_len;
        memcpy(&sHostRequestA, request_receive_buffer, bytes_to_copy);
        memmove(request_receive_buffer, request_receive_buffer + bytes_to_copy,
                request_receive_pos - bytes_to_copy);
        request_receive_pos = (uint16_t) (request_receive_pos - bytes_to_copy);
        isHostRequestAReady = true;

        CHECK_GLOBAL_STATUS(ERROR_STATE_OK);
    }

    if (isHostRequestBReady == false)
    {
        size_t bytes_to_copy = sizeof(s_host_request_t) + packet_len;
        memcpy(&sHostRequestB, request_receive_buffer, bytes_to_copy);
        memmove(request_receive_buffer, request_receive_buffer + bytes_to_copy,
                request_receive_pos - bytes_to_copy);
        request_receive_pos = (uint16_t) (request_receive_pos - bytes_to_copy);
        isHostRequestBReady = true;
    }

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

static uint16_t hostInterface_checkPayloadSize(uint16_t length)
{
    if (length > XFER_MAX_PAYLOAD_SIZE)
    {
        length = XFER_MAX_PAYLOAD_SIZE;
    }

    return length;
}

static GLOBAL_STATUS hostInterface_checkRequestPackageLength(const s_host_request_t *rq,
                                                             s_device_reply_t *rp, uint16_t length,
                                                             const char *msg)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    if (rq->len != length)
    {
        hostInterface_reply_err(rp, msg, itox32(rq->len));
        CHECK_GLOBAL_STATUS(ERROR_STATE_SIZE_INVALID);
    }

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

static GLOBAL_STATUS hostInterface_handle_request(s_host_request_t *rq, s_device_reply_t *rp)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    uint16_t len = 0;
    size_t s = 0;

    rp->magic = DEV_REPL_MAGIC;
    rp->id = rq->id;
    switch (rq->type)
    {
        case HOST_REQ_ROM_SEEK:
            CHECK_GLOBAL_STATUS(hostInterface_checkRequestPackageLength(
                    rq, rp, 4, "ERROR: gba rom address seek: len != 4: %s"));

            gba.rom_word_addr = (size_t) (rq->data[0] | (rq->data[1] << 8) | (rq->data[2] << 16) |
                                          (rq->data[3] << 24));
            gba.rom_word_addr >>= 1;
            rp->type = DEV_REPL_ROM_SEEK;
            rp->len = 0;
            break;
        case HOST_REQ_ROM_READ:
            CHECK_GLOBAL_STATUS(hostInterface_checkRequestPackageLength(
                    rq, rp, 2, "ERROR: gba rom read len: len != 2: %s"));

            len = hostInterface_checkPayloadSize((uint16_t) (rq->data[0] | (rq->data[1] << 8)));
            gba_cart_rom_read(gba.rom_word_addr, (uint16_t *) rp->data, len / 2);
            gba.rom_word_addr += (uint16_t) (len / 2);
            rp->type = DEV_REPL_ROM_READ;
            rp->len = len;
            break;
        case HOST_REQ_ROM_WRITE:
            len = hostInterface_checkPayloadSize(rq->len);
            gba_cart_rom_write(gba.rom_word_addr, (uint16_t *) rq->data, len / 2);
            gba.rom_word_addr += (uint16_t) (len / 2);
            rp->type = DEV_REPL_ROM_WRITE;
            rp->len = 0;
            break;
        case HOST_REQ_ROM_SIZE:
            rp->type = DEV_REPL_ROM_SIZE;
            s = gba_cart_rom_size();
            rp->data[0] = (uint8_t) s;
            rp->data[1] = (uint8_t) (s >> 8);
            rp->data[2] = (uint8_t) (s >> 16);
            rp->data[3] = (uint8_t) (s >> 24);
            rp->len = 4;
            break;
        case HOST_REQ_BKP_TYPE:
            rp->type = DEV_REPL_BKP_TYPE;
            s = gba_cart_save_size();
            rp->data[0] = (uint8_t) s;
            rp->data[1] = (uint8_t) (s >> 8);
            rp->data[2] = (uint8_t) (s >> 16);
            rp->data[3] = (uint8_t) (s >> 24);
            rp->len = 4;
            break;
        case HOST_REQ_SRAM_SEEK:
        case HOST_REQ_FLASH_SEEK:
            CHECK_GLOBAL_STATUS(hostInterface_checkRequestPackageLength(
                    rq, rp, 2, "ERROR: gba sram address seek: len != 2: %s"));

            gba.sram_byte_addr = (uint16_t) (rq->data[0] | (rq->data[1] << 8));
            if (rq->type == HOST_REQ_SRAM_SEEK)
            {
                rp->type = DEV_REPL_SRAM_SEEK;
            }
            else
            {
                rp->type = DEV_REPL_FLASH_SEEK;
            }
            rp->len = 0;
            break;
        case HOST_REQ_SRAM_READ:
        case HOST_REQ_FLASH_READ:
            CHECK_GLOBAL_STATUS(hostInterface_checkRequestPackageLength(
                    rq, rp, 2, "ERROR: gba sram read len: len != 2: %s"));

            len = hostInterface_checkPayloadSize((uint16_t) (rq->data[0] | (rq->data[1] << 8)));

            gba_cart_sram_read(gba.sram_byte_addr, rp->data, len);
            gba.sram_byte_addr = (uint16_t) (gba.sram_byte_addr + len);
            if (rq->type == HOST_REQ_SRAM_READ)
            {
                rp->type = DEV_REPL_SRAM_READ;
            }

            else
            {
                rp->type = DEV_REPL_FLASH_READ;
            }
            rp->len = len;
            break;
        case HOST_REQ_SRAM_WRITE:
            len = hostInterface_checkPayloadSize(rq->len);
            gba_cart_sram_write(gba.sram_byte_addr, rq->data, len);
            gba.sram_byte_addr = (uint16_t) (gba.sram_byte_addr + len);
            rp->type = DEV_REPL_SRAM_WRITE;
            rp->len = 0;
            break;
        case HOST_REQ_FLASH_ERASE:
            if (gba_cart_flash_erase())
            {
                rp->type = DEV_REPL_FLASH_ERASE;
                rp->len = 0;
            }
            else
            {
                hostInterface_reply_err(rp, "ERROR: gba flash erase timed out");
                CHECK_GLOBAL_STATUS(ERROR_STATE_TIMEOUT);
            }
            break;
        case HOST_REQ_FLASH_WRITE:
            len = hostInterface_checkPayloadSize(rq->len);

            if (gba_cart_flash_write(gba.sram_byte_addr, rq->data, len))
            {
                gba.sram_byte_addr = (uint16_t) (gba.sram_byte_addr + len);
                rp->type = DEV_REPL_FLASH_WRITE;
                rp->len = 0;
            }
            else
            {
                hostInterface_reply_err(rp, "ERROR: gba flash write timed out");
                CHECK_GLOBAL_STATUS(ERROR_STATE_SIZE_INVALID);
            }
            break;
        case HOST_REQ_FLASH_BANK:
            CHECK_GLOBAL_STATUS(hostInterface_checkRequestPackageLength(
                    rq, rp, 1, "ERROR: gba flash bank: len != 2: %s"));

            gba_cart_flash_switch_bank(rq->data[0]);
            rp->type = DEV_REPL_FLASH_BANK;
            rp->len = 0;
            break;
        case HOST_REQ_EEPROM512_SEEK:
        case HOST_REQ_EEPROM8K_SEEK:
            CHECK_GLOBAL_STATUS(hostInterface_checkRequestPackageLength(
                    rq, rp, 2, "ERROR: gba eeprom address seek: len != 2: %s"));

            gba.eeprom_block_addr = (uint16_t) (rq->data[0] | (rq->data[1] << 8));
            gba.eeprom_block_addr >>= 3;
            gba.eeprom_block_addr &= 0x3FF;
            if (rq->type == HOST_REQ_EEPROM512_SEEK)
            {
                rp->type = DEV_REPL_EEPROM512_SEEK;
            }
            else
            {
                rp->type = DEV_REPL_EEPROM8K_SEEK;
            }
            rp->len = 0;
            break;
        case HOST_REQ_EEPROM512_READ:
            gba_cart_eeprom_512_read_data(gba.eeprom_block_addr++, rp->data);
            rp->type = DEV_REPL_EEPROM512_READ;
            rp->len = 8;
            break;
        case HOST_REQ_EEPROM8K_READ:
            gba_cart_eeprom_8k_read_data(gba.eeprom_block_addr++, rp->data);
            rp->type = DEV_REPL_EEPROM8K_READ;
            rp->len = 8;
            break;
        case HOST_REQ_EEPROM512_WRITE:
            CHECK_GLOBAL_STATUS(hostInterface_checkRequestPackageLength(
                    rq, rp, 8, "ERROR: gba eeprom512 write: len != 8: %s"));

            if (gba_cart_eeprom_512_write_data(gba.eeprom_block_addr++, rq->data))
            {
                rp->type = DEV_REPL_EEPROM512_WRITE;
                rp->len = 0;
            }
            else
            {
                hostInterface_reply_err(rp, "ERROR: gba eeprom512 write timed out");
                CHECK_GLOBAL_STATUS(ERROR_STATE_TIMEOUT);
            }
            break;
        case HOST_REQ_EEPROM8K_WRITE:
            CHECK_GLOBAL_STATUS(hostInterface_checkRequestPackageLength(
                    rq, rp, 8, "ERROR: gba eeprom8k write: len != 8: %s"));

            if (gba_cart_eeprom_8k_write_data(gba.eeprom_block_addr++, rq->data))
            {
                rp->type = DEV_REPL_EEPROM8K_WRITE;
                rp->len = 0;
            }
            else
            {
                hostInterface_reply_err(rp, "ERROR: gba eeprom8k write timed out");
                CHECK_GLOBAL_STATUS(ERROR_STATE_TIMEOUT);
            }
            break;
        case HOST_REQ_UART_SYNC:
            rp->type = DEV_REPL_UART_SYNC;
            rp->len = 0;
            break;
        case HOST_REQ_NDS_ROM_SEEK:
            CHECK_GLOBAL_STATUS(hostInterface_checkRequestPackageLength(
                    rq, rp, 4, "ERROR: nds rom seek len != 4: %s"));

            nds.rom_byte_addr = (size_t) (rq->data[0] | (rq->data[1] << 8) | (rq->data[2] << 16) |
                                          (rq->data[3] << 24));
            rp->type = DEV_REPL_NDS_ROM_SEEK;
            rp->len = 0;
            break;
        case HOST_REQ_NDS_ROM_READ:
            CHECK_GLOBAL_STATUS(hostInterface_checkRequestPackageLength(
                    rq, rp, 2, "ERROR: nds rom read len != 2: %s"));

            len = hostInterface_checkPayloadSize((uint16_t) (rq->data[0] | (rq->data[1] << 8)));
            nds_cart_rom_read(nds.rom_byte_addr, rp->data, len);
            nds.rom_byte_addr += len;
            rp->type = DEV_REPL_NDS_ROM_READ;
            rp->len = len;
            break;
        case HOST_REQ_NDS_ROM_CHIPID:
            nds_cart_cmd_chip_id(rp->data);
            rp->type = DEV_REPL_NDS_ROM_CHIPID;
            rp->len = 4;
            break;
        case HOST_REQ_NDS_ROM_INIT:
            if (nds_cart_rom_init())
            {
                rp->type = DEV_REPL_NDS_ROM_INIT;
                rp->len = 0;
            }
            else
            {
                hostInterface_reply_err(
                        rp, "ERROR: nds rom could not be initialized, see UART for details");
                CHECK_GLOBAL_STATUS(ERROR_STATE_ROM_NOT_INITIALIZED);
            }
            break;
        default:
            hostInterface_reply_err(rp, "ERROR: invalid request ID: %s", itox32(rq->type));
            CHECK_GLOBAL_STATUS(ERROR_STATE_INVALID_PARAMETER);
    }

    status = ERROR_STATE_OK;
EXIT:
    if (hostInterface_send_reply() != ERROR_STATE_OK)
    {
        status = ERROR_STATE_CDC_TRANSMIT_FAIL;
    }
    return status;
}

static GLOBAL_STATUS hostInterface_send_reply(void)
{
    return usb_send_data(&sDeviceReply, (uint16_t) (sizeof(s_device_reply_t) + sDeviceReply.len));
}

static void hostInterface_reply_err(s_device_reply_t *rp, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    rp->type = DEV_REPL_ERR;
    rp->len = (uint16_t) vsnprintf((char *) rp->data, XFER_MAX_PAYLOAD_SIZE, msg, args);
    va_end(args);
}
