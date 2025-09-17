#ifndef HW_CONFIG_H
#define HW_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

/*
 * Wiring:
 * PORTA[0..7]  <-> GBA_A[16..23]
 * PORTA[8]     <-> GBA_NWR
 * PORTA[13]    <-> GBA_NRD
 * PORTA[14]    <-> GBA_NCS
 * PORTA[15]    <-> GBA_NCS2
 *
 * PORTB[0..15] <-> GBA_AD[0..15]
 *
 * PORTC[12]    <-> LVL_SHIFT_A
 * PORTD[2]     <-> LVL_SHIFT_AD
 */

#define EEPROM_WORD_ADDR 0xFFFF80

#define PIN_ADBUS 2u
#define PIN_ADBUS_MSK (1u << PIN_ADBUS)
#define PIN_NWR 8u
#define PIN_NWR_MSK (1u << PIN_NWR)
#define PIN_UABUS 12u
#define PIN_UABUS_MSK (1u << PIN_UABUS)
#define PIN_NRD 13u
#define PIN_NRD_MSK (1u << PIN_NRD)
#define PIN_NCS 14u
#define PIN_NCS_MSK (1u << PIN_NCS)
#define PIN_NCS2 15u
#define PIN_NCS2_MSK (1u << PIN_NCS2)

#define NCS_LOW()                                                                                  \
    gpio_clear(GPIOA, PIN_NCS_MSK);                                                                \
    GBA_CART_DELAY();
#define NCS_HIGH()                                                                                 \
    gpio_set(GPIOA, PIN_NCS_MSK);                                                                  \
    GBA_CART_DELAY();
#define NCS2_LOW()                                                                                 \
    gpio_clear(GPIOA, PIN_NCS2_MSK);                                                               \
    GBA_CART_DELAY();
#define NCS2_HIGH()                                                                                \
    gpio_set(GPIOA, PIN_NCS2_MSK);                                                                 \
    GBA_CART_DELAY();
#define NRD_LOW()                                                                                  \
    gpio_clear(GPIOA, PIN_NRD_MSK);                                                                \
    GBA_CART_DELAY();
#define NRD_HIGH()                                                                                 \
    gpio_set(GPIOA, PIN_NRD_MSK);                                                                  \
    GBA_CART_DELAY();
#define NWR_LOW()                                                                                  \
    gpio_clear(GPIOA, PIN_NWR_MSK);                                                                \
    GBA_CART_DELAY();
#define NWR_HIGH()                                                                                 \
    gpio_set(GPIOA, PIN_NWR_MSK);                                                                  \
    GBA_CART_DELAY();

#define ADBUS_LEVEL_DIR_INPUT() gpio_clear(GPIOD, PIN_ADBUS_MSK)
#define ADBUS_LEVEL_DIR_OUTPUT() gpio_set(GPIOD, PIN_ADBUS_MSK)
#define UABUS_LEVEL_DIR_INPUT() gpio_clear(GPIOC, PIN_UABUS_MSK)
#define UABUS_LEVEL_DIR_OUTPUT() gpio_set(GPIOC, PIN_UABUS_MSK)

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

#define NDS_PAGE_SIZE 0x1000
#define NDS_CHUNK_SIZE 0x200
#define NDS_SMALL_HEADER_SIZE 0x200
#define NDS_EXT_HEADER_SIZE 0x1000

#define PIN_CLK 8u
#define PIN_CLK_MSK (1u << PIN_CLK)
#define PIN_ROMCS 9u
#define PIN_ROMCS_MSK (1u << PIN_ROMCS)
#define PIN_RESET 10u
#define PIN_RESET_MSK (1u << PIN_RESET)
#define PIN_EEPROMCS 11u
#define PIN_EEPROMCS_MSK (1u << PIN_EEPROMCS)

#define CLK_HIGH() gpio_set(GPIOC, PIN_CLK_MSK)
#define CLK_LOW() gpio_clear(GPIOC, PIN_CLK_MSK)
#define ROMCS_HIGH() gpio_set(GPIOC, PIN_ROMCS_MSK)
#define ROMCS_LOW() gpio_clear(GPIOC, PIN_ROMCS_MSK)
#define RESET_HIGH() gpio_set(GPIOC, PIN_RESET_MSK)
#define RESET_LOW() gpio_clear(GPIOC, PIN_RESET_MSK)
#define EEPROMCS_HIGH() gpio_set(GPIOC, PIN_EEPROMCS_MSK)
#define EEPROMCS_LOW() gpio_clear(GPIOC, PIN_EEPROMCS_MSK)

#define DATA_IN_CYCLE_42() data_in_cycle(8)
#define DATA_IN_CYCLE_67() data_in_cycle(5)
#define DATA_OUT_CYCLE_42(d) data_out_cycle(d, 8)
#define DATA_OUT_CYCLE_67(d) data_out_cycle(d, 5)

__STATIC_FORCEINLINE void wait_cycles(size_t cycles)
{
#pragma GCC unroll 64
    for (size_t i = 0; i < cycles; i++)
    {
        __asm__ volatile("nop");
    }
}

__STATIC_FORCEINLINE void gpio_set(GPIO_TypeDef *pPort, uint32_t mask) { pPort->BSRR = mask; }

__STATIC_FORCEINLINE void gpio_clear(GPIO_TypeDef *pPort, uint32_t mask)
{
    pPort->BSRR = mask << 16;
}

__STATIC_FORCEINLINE void configDataLanesAsInput(GPIO_TypeDef *pPort, e_pin_group group)
{
    switch (group)
    {
        case E_PIN_GROUP_0_7:
            {
                pPort->CRL = 0x44444444;
            }
            break;
        case E_PIN_GROUP_8_15:
            {
                pPort->CRH = 0x44444444;
            }
            break;
    }
}

__STATIC_FORCEINLINE void configDataLanesAsOutput(GPIO_TypeDef *pPort, e_pin_group group)
{
    switch (group)
    {
        case E_PIN_GROUP_0_7:
            {
                pPort->CRL = 0x11111111;
            }
            break;
        case E_PIN_GROUP_8_15:
            {
                pPort->CRH = 0x11111111;
            }
            break;
    }
}

__STATIC_FORCEINLINE uint8_t data_in_cycle(size_t cycles)
{
    uint8_t data = 0;

    CLK_LOW();
    wait_cycles(cycles);
    data = GPIOC->IDR;
    CLK_HIGH();
    wait_cycles(cycles);

    return data;
}

__STATIC_FORCEINLINE void data_out_cycle(uint8_t d, size_t cycles)
{
    uint8_t nv = 0;

    CLK_LOW();
    nv = (uint8_t) ~d;
    GPIOC->BSRR = (uint32_t) (d | (nv << 16));
    wait_cycles(cycles);
    CLK_HIGH();
    wait_cycles(cycles);
}

#ifdef __cplusplus
}
#endif

#endif // HW_CONFIG_H
