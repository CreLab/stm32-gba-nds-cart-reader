#include "print.h"
#include "string.h"

GLOBAL_STATUS print_chip_id(const s_nds_chip_id *id)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    uint8_t bid[4];
    memcpy(bid, id, 4);
    CHECK_GLOBAL_STATUS(uart_printf("chip_id: %02x %02x %02x %02x\r\n", bid[0], bid[1], bid[2], bid[3]));

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS print_keybuf(const char *pMsg, s_blowfish_t *pKeyBuf)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    const uint8_t *keybuf = (const uint8_t *) pKeyBuf;

    CHECK_GLOBAL_STATUS(uart_printf("%s:\r\n", pMsg));

    for (size_t i = 0; i < sizeof(s_blowfish_t); i++)
    {
        CHECK_GLOBAL_STATUS(uart_printf(" %02x", keybuf[i]));
    }

    CHECK_GLOBAL_STATUS(uart_printf("\r\n"));

    status = ERROR_STATE_OK;
EXIT:
    return status;
}
