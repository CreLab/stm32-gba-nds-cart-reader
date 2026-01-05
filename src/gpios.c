#include "gpios.h"

/*
 * Wiring:
 * PORTC[0..7]  <-> NDS_DATA[0..7]
 * PORTC[8]     <-> NDS_CLK
 * PORTC[9]     <-> NDS_ROMCS
 * PORTC[10]    <-> NDS_RESET
 * PORTC[11]    <-> NDS_EEPROMCS
 *
 * On all transfers, data should be stable at rising edge of CLK
 */

#define PIN_CLK 8u
#define PIN_CLK_MSK (1u << PIN_CLK)
#define PIN_ROMCS 9u
#define PIN_ROMCS_MSK (1u << PIN_ROMCS)
#define PIN_RESET 10u
#define PIN_RESET_MSK (1u << PIN_RESET)
#define PIN_EEPROMCS 11u
#define PIN_EEPROMCS_MSK (1u << PIN_EEPROMCS)

__attribute__((always_inline)) inline void clk_low(void) { GPIOC->BSRR = PIN_CLK_MSK << 16; }

__attribute__((always_inline)) inline void clk_high(void) { GPIOC->BSRR = PIN_CLK_MSK; }

__attribute__((always_inline)) inline void romcs_low(void)
{
    GPIOC->BSRR = PIN_ROMCS_MSK << 16;
}

__attribute__((always_inline)) inline void romcs_high(void) { GPIOC->BSRR = PIN_ROMCS_MSK; }

__attribute__((always_inline)) inline void reset_low(void)
{
    GPIOC->BSRR = PIN_RESET_MSK << 16;
}

__attribute__((always_inline)) inline void reset_high(void) { GPIOC->BSRR = PIN_RESET_MSK; }

__attribute__((always_inline)) inline void eepromcs_low(void)
{
    GPIOC->BSRR = PIN_EEPROMCS_MSK << 16;
}

__attribute__((always_inline)) inline void eepromcs_high(void)
{
    GPIOC->BSRR = PIN_EEPROMCS_MSK;
}

__attribute__((always_inline)) inline void data_dir_input(void) { GPIOC->CRL = 0x44444444; }

__attribute__((always_inline)) inline uint8_t data_input(void)
{
    return (uint8_t) GPIOC->IDR;
}

__attribute__((always_inline)) inline void data_dir_output(void) { GPIOC->CRL = 0x11111111; }

__attribute__((always_inline)) inline void data_output(uint8_t v)
{
    uint8_t nv = (uint8_t) ~v;
    GPIOC->BSRR = (uint32_t) (v | (nv << 16));
}
