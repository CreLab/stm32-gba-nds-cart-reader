#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32f1xx_hal.h"

#define CHECK_STATUS(ret) if (ret != HAL_OK) { \
    status = ret; \
    goto EXIT; \
    } \

__attribute__((always_inline)) static inline void NOP(void)
{
    __asm__("\tnop");
}

__attribute__((always_inline)) static inline void WAIT(size_t x)
{
    // __asm__ volatile(
    //         ".Ldelay_loop_%=:\n\t"
    //         "subs %[cnt], #1\n\t"
    //         "bhi .Ldelay_loop_%=\n\t"
    //         : [cnt] "+r" (x) :: "cc"
    //        );
}

typedef struct {
    uint32_t P[16 + 2];
    uint32_t S[4][256];
} s_blowfish_t;

void usb_send_data(const void *data, uint16_t len);
void usb_print_bytes(const void *data, uint16_t len);
void usb_printf(const char *msg, ...);

void uart_send_data(const void *data, uint16_t len);
void uart_print_bytes(const void *data, uint16_t len);
void uart_printf(const char *msg, ...);

void print_keybuf(const char *pMsg, s_blowfish_t* pKeyBuf);

const char *itox8(uint8_t x);
const char *itox32(uint32_t x);

uint64_t bitrev_64(uint64_t x);

#define ceil_div(num, den) (((num) + (den) - 1) / (den))

#ifndef NDEBUG
#define myassert(cond, fmt, ...) \
    do { \
        if (!(cond)) { \
            uart_printf("Assertion Failed in %s:%d function %s\r\n", __FILE__, __LINE__, __func__); \
            uart_printf((fmt), ## __VA_ARGS__); \
            while (1) { __asm__("nop"); } \
        } \
    } while (0)
#else
#define myassert(...) do { } while(0)
#endif

#ifdef DEBUG
#define DEBUG_PRINTF(pMsg, ...) uart_printf(pMsg, ## __VA_ARGS__)
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

#define WALGN __attribute__((aligned(4)))

#ifdef __cplusplus
}
#endif

#endif /* UTIL_H */