#ifndef GPIOS_H
#define GPIOS_H

#include "util.h"

/* Pin settings of NDS slot:
 * PORTC[0..7]  <-> NDS_DATA[0..7]
 * PORTC[8]     <-> NDS_CLK
 * PORTC[9]     <-> NDS_ROMCS
 * PORTC[10]    <-> NDS_RESET
 * PORTC[11]    <-> NDS_EEPROMCS
 */

#define PIN_MISO        GPIO_PIN_6
#define PIN_MOSI        GPIO_PIN_7
#define PIN_CLK         GPIO_PIN_8
#define PIN_ROMCS       GPIO_PIN_9
#define PIN_RESET       GPIO_PIN_10
#define PIN_EEPROMCS    GPIO_PIN_11

#define GPIOC_SET_PIN(pin)   (GPIOC->BSRR = pin)
#define GPIOC_CLR_PIN(pin)   (GPIOC->BSRR = (uint32_t)pin << 16)

/* The hardware is running with 72 MHz (72 cycles pro µs)
 * wait_cycles needs 2 cycles pro iteration,
 * thats why it needs a factor of 2
 * */
#define CYCLES_PER_US  36

#define ONE_MHZ_IN_CYCLES  18
#define FOUR_MHZ_IN_CYCLES  8
#define SIX_MHZ_IN_CYCLES   5

#define delay_us(us) wait_cycles(us * CYCLES_PER_US)

__attribute__((always_inline)) static inline void wait_cycles(uint32_t cycles)
{
#if 0

    if (cycles < 3) return; // Overhead-Schutz für extrem kleine Werte

    // Wir teilen durch 3, da SUBS + BNE zusammen 3 Zyklen benötigen
    uint32_t iterations = cycles / 3;

    __asm__ volatile (
        ".syntax unified     \n"
        "1: subs %[it], #1   \n" // 1 Zyklus
        "   bne 1b           \n" // 2 Zyklen (wenn Sprung ausgeführt wird)
        : [it] "+r" (iterations)
        :
        : "cc"                   // "cc" informiert den Compiler, dass Flags (Condition Codes) geändert werden
    );
#else
#pragma GCC unroll 64
    for (size_t i = 0; i < cycles; i++)
    {
        __asm__ volatile("nop");
    }
#endif
}

GLOBAL_STATUS MX_GPIO_Init(void);

#endif // GPIOS_H
