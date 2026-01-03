#include <stdarg.h>
#include <stdio.h>

#include "usart.h"
#include "usbd_cdc_if.h"
#include "util.h"

#define INT_TO_DISP_CHAR(i) (((i) <= 9) ? (char) ('0' + (i)) : (char) ('A' + (i) - 10))
#define NUM_ITOX8 16
#define NUM_ITOX32 4

#define BOOT_MAGIC_VALUE  ((uint64_t)0xDEADBEEFCC00FFEEULL)

extern uint8_t _dfu_boot_mode;

GLOBAL_STATUS usb_send_data(const void *data, uint16_t len)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    uint8_t *txData = (uint8_t*)data;

    while (len > 0)
    {
        uint16_t block_len = len;
        if (block_len > sizeof(UserTxBufferFS))
        {
            block_len = sizeof(UserTxBufferFS);
        }

        extern USBD_HandleTypeDef hUsbDeviceFS;
        USBD_CDC_HandleTypeDef *hcdc = hUsbDeviceFS.pClassData;

        while (hcdc->TxState != 0)
        {
        }

        memcpy(UserTxBufferFS, txData, block_len);
        if (CDC_Transmit_FS(UserTxBufferFS, block_len) != USBD_OK)
        {
            CHECK_GLOBAL_STATUS(ERROR_STATE_CDC_TRANSMIT_FAIL);
        }

        txData = txData + block_len;
        len = (uint16_t) (len - block_len);
    }

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS usb_print_bytes(const void *data, uint16_t len)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    if (len > 64)
    {
        len = 64;
    }

    char out[256] = {0};
    out[0] = '\0';
    const char *input = data;

    while (len-- > 0)
    {
        strcat(out, itox8((uint8_t) *input++));
        strcat(out, ",");
    }

    CHECK_GLOBAL_STATUS(usb_printf("%s\r\n", out));

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS usb_printf(const char *msg, ...)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    va_list args;
    va_start(args, msg);

    char out[256] = {0};
    int len = vsnprintf(out, sizeof(out), msg, args);
    CHECK_GLOBAL_STATUS(usb_send_data(out, (uint16_t) len));

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS uart_send_data(const void *data, uint16_t len)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    if (HAL_UART_Transmit(Get_USART1_UART_Handle(), (void *) data, len, HAL_MAX_DELAY) != HAL_OK)
    {
        CHECK_GLOBAL_STATUS(ERROR_STATE_UART_TRANSMIT_FAIL);
    }

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS uart_print_bytes(const void *data, uint16_t len)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    if (len > 64)
    {
        len = 64;
    }

    char out[256] = {0};
    out[0] = '\0';
    const char *input = data;

    while (len-- > 0)
    {
        strcat(out, itox8((uint8_t) *input++));
        strcat(out, ",");
    }

    CHECK_GLOBAL_STATUS(uart_printf("%s\r\n", out));

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

GLOBAL_STATUS uart_printf(const char *msg, ...)
{
    GLOBAL_STATUS status = ERROR_STATE_NONE;

    va_list args;
    va_start(args, msg);

    char out[256] = {0};
    int len = vsnprintf(out, sizeof(out), msg, args);
    CHECK_GLOBAL_STATUS(uart_send_data(out, (uint16_t) len));

    va_end(args);

    status = ERROR_STATE_OK;
EXIT:
    return status;
}

const char *itox8(uint8_t x)
{
    static char strs[NUM_ITOX8][3];
    static uint8_t str_index = 0;
    char *str = strs[str_index];

    str[0] = INT_TO_DISP_CHAR(x >> 4);
    str[1] = INT_TO_DISP_CHAR(x & 0xF);
    str[2] = '\0';
    str_index = (uint8_t) ((str_index + 1) % NUM_ITOX8);

    return str;
}

const char *itox32(uint32_t x)
{
    static char strs[NUM_ITOX32][9];
    static uint8_t str_index = 0;
    char *str = strs[str_index];

    for (uint32_t i = 0; i < 8; i++)
    {
        uint32_t nibble = x >> 28;
        str[i] = INT_TO_DISP_CHAR(nibble);
        x <<= 4;
    }

    str[8] = '\0';
    str_index = (uint8_t) ((str_index + 1) % NUM_ITOX32);

    return str;
}

uint64_t bitrev_64(uint64_t x)
{
    uint64_t result = 0;

    for (size_t i = 0; i < 64; i++)
    {
        result <<= 1;
        result |= x & 1;
        x >>= 1;
    }

    return result;
}

void boot_into_dfu_bootloader(void)
{
    volatile uint64_t *boot_magic =
            (volatile uint64_t *)&_dfu_boot_mode;

    *boot_magic = BOOT_MAGIC_VALUE;

    // Sicherstellen, dass der Schreibzugriff wirklich im RAM landet
    __DSB();
    __ISB();

    // Hardware-Reset auslösen (Cortex-M)
    NVIC_SystemReset();

    // Fallback, falls aus irgendeinem Grund kein Reset passiert
    for (;;)
    {
        __NOP();
    }
}


void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
    uart_printf("ASSERTION FAILED:\n  EXPR: %s\n  FILE: %s\n  FUNC: %s\n  LINE: %d", failedexpr,
                file, func, line);

    while (1)
    {
        __asm__ volatile("nop");
    }
}
