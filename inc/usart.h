#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nds_cart.h"

#ifndef NDEBUG
#define myassert(cond, fmt, ...)                                                                   \
    do                                                                                             \
    {                                                                                              \
        if (!(cond))                                                                               \
        {                                                                                          \
            uart_printf("Assertion Failed in %s:%d function %s\r\n", __FILE__, __LINE__,           \
                        __func__);                                                                 \
            uart_printf((fmt), ##__VA_ARGS__);                                                     \
            while (1)                                                                              \
            {                                                                                      \
                __asm__("nop");                                                                    \
            }                                                                                      \
        }                                                                                          \
    }                                                                                              \
    while (0)
#else
#define myassert(...)                                                                              \
    do                                                                                             \
    {                                                                                              \
    }                                                                                              \
    while (0)
#endif

#ifdef DEBUG
#define DEBUG_PRINTF(pMsg, ...) uart_printf(pMsg, ##__VA_ARGS__)
#define DEBUG_PRINT(pMsg) uart_printf(pMsg, NULL)
#else
#define DEBUG_PRINTF(pMsg, ...)
#define DEBUG_PRINT(pMsg)
#endif

#ifdef DEBUG
#define PRINT_KEY_BUFFER(pMsg, pBuf) print_keybuf(pMsg, pBuf)
#else
#define PRINT_KEY_BUFFER(pMsg, pBuf)
#endif

GLOBAL_STATUS MX_USART1_UART_Init(void);

GLOBAL_STATUS uart_send_data(const void *data, uint16_t len);
GLOBAL_STATUS uart_print_bytes(const void *data, uint16_t len);
GLOBAL_STATUS uart_printf(const char *msg, ...);

GLOBAL_STATUS print_keybuf(const char *pMsg, s_blowfish_t *pKeyBuf);
GLOBAL_STATUS print_chip_id(const struct nds_chip_id *id);

#ifdef __cplusplus
}
#endif

#endif /*__USART_H */
