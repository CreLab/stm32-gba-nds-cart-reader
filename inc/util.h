#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "stm32f1xx_hal.h"

#define GLOBAL_STATUS e_error_state

#define CHECK_GLOBAL_STATUS(ret)                                                                   \
    if (ret != ERROR_STATE_OK)                                                                     \
    {                                                                                              \
        status = ret;                                                                              \
        goto EXIT;                                                                                 \
    }

#define FORCE_INLINE __attribute__((always_inline)) inline

typedef enum e_pin_group
{
    E_PIN_GROUP_0_7,
    E_PIN_GROUP_8_15,
} e_pin_group;

typedef enum e_error_state
{
    ERROR_STATE_NONE = 0,
    ERROR_STATE_OK,
    ERROR_STATE_OSC_INIT_FAIL,
    ERROR_STATE_CLK_INIT_FAIL,
    ERROR_STATE_PERIPH_CLK_FAIL,
    ERROR_STATE_BUFFER_OVERFLOW,
    ERROR_STATE_SIZE_INVALID,
    ERROR_STATE_POS_MISMATCH,
    ERROR_STATE_CDC_TRANSMIT_FAIL,
    ERROR_STATE_INVALID_PARAMETER,
    ERROR_STATE_ROM_NOT_INITIALIZED,
    ERROR_STATE_TIMEOUT,
    ERROR_STATE_UART_INIT,
    ERROR_STATE_UART_TRANSMIT_FAIL,
    ERROR_STATE_GPIO_INIT,
} e_error_state;

__STATIC_FORCEINLINE void NOP(void) { __asm__("\tnop"); }

__STATIC_FORCEINLINE void WAIT(size_t x)
{
    // __asm__ volatile(
    //         ".Ldelay_loop_%=:\n\t"
    //         "subs %[cnt], #1\n\t"
    //         "bhi .Ldelay_loop_%=\n\t"
    //         : [cnt] "+r" (x) :: "cc"
    //        );
}

typedef struct
{
    uint32_t P[16 + 2];
    uint32_t S[4][256];
} s_blowfish_t;

GLOBAL_STATUS usb_send_data(const void *data, uint16_t len);
GLOBAL_STATUS usb_print_bytes(const void *data, uint16_t len);
GLOBAL_STATUS usb_printf(const char *msg, ...);

const char *itox8(uint8_t x);
const char *itox32(uint32_t x);

uint64_t bitrev_64(uint64_t x);

#define ceil_div(num, den) (((num) + (den) - 1) / (den))

#define WALGN __attribute__((aligned(4)))

#ifdef __cplusplus
}
#endif

#endif /* UTIL_H */
