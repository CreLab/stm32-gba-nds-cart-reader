#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32f1xx_hal.h"

#if 0
    #define CPU_RUNNING_TEST
    #define ERROR_INTERRUPT_SIGNALS
#endif

#define GLOBAL_STATUS e_error_state

#define CHECK_GLOBAL_STATUS(ret)                                                                   \
    if (ret != ERROR_STATE_OK)                                                                     \
    {                                                                                              \
        status = ret;                                                                              \
        goto EXIT;                                                                                 \
    }

#define RETURN_GLOBAL_STATUS(ret)                                                              \
    status = ret;                                                                              \
    goto EXIT;                                                                                 \

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

__attribute__((always_inline)) static inline void NOP(void) { __asm__("\tnop"); }

__attribute__((always_inline)) static inline void WAIT(size_t x)
{
    (void)x;
    // __asm__ volatile(
    //         ".Ldelay_loop_%=:\n\t"
    //         "subs %[cnt], #1\n\t"
    //         "bhi .Ldelay_loop_%=\n\t"
    //         : [cnt] "+r" (x) :: "cc"
    //        );
}

GLOBAL_STATUS usb_send_data(const void *data, uint16_t len);
GLOBAL_STATUS usb_print_bytes(const void *data, uint16_t len);
GLOBAL_STATUS usb_printf(const char *msg, ...);

GLOBAL_STATUS uart_send_data(const void *data, uint16_t len);
GLOBAL_STATUS uart_print_bytes(const void *data, uint16_t len);
GLOBAL_STATUS uart_printf(const char *msg, ...);

#ifdef ERROR_INTERRUPT_SIGNALS
void HAL_UART_DebugSignal(void);
void HAL_UART_DebugSignal_RX(GPIO_PinState state);
void HAL_UART_DebugSignal_TX(GPIO_PinState state);
void HAL_UART_DebugPeriodSignal_RX(uint32_t time);
void HAL_UART_DebugPeriodSignal_TX(uint32_t time);

#define DBG_SIGNAL_INIT()           HAL_UART_DebugSignal()
#define DBG_SIGNAL_RX(state)        HAL_UART_DebugSignal_RX(state)
#define DBG_SIGNAL_TX(state)        HAL_UART_DebugSignal_TX(state)
#define DBG_PERIOD_SIGNAL_RX(time)  HAL_UART_DebugPeriodSignal_RX(time)
#define DBG_PERIOD_SIGNAL_TX(time)  HAL_UART_DebugPeriodSignal_TX(time)
#else
#define DBG_SIGNAL_INIT()
#define DBG_SIGNAL_RX(state)
#define DBG_SIGNAL_TX(state)
#define DBG_PERIOD_SIGNAL_RX(time)
#define DBG_PERIOD_SIGNAL_TX(time)
#endif

const char *itox8(uint8_t x);
const char *itox32(uint32_t x);

uint64_t bitrev_64(uint64_t x);

void boot_into_dfu_bootloader(void);

#define ceil_div(num, den) (((num) + (den) - 1) / (den))

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

#define WALGN __attribute__((aligned(4)))

#ifdef __cplusplus
}
#endif

#endif /* UTIL_H */
