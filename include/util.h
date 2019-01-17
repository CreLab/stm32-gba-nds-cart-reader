#pragma once

#include <stdint.h>

__attribute__((always_inline)) static inline void NOP(void)
{
    __asm__("\tnop");
}

void usb_send_data(const void *data, uint16_t len);
void usb_print_bytes(const void *data, uint16_t len);
void usb_printf(const char *msg, ...);

void uart_send_data(const void *data, uint16_t len);
void uart_print_bytes(const void *data, uint16_t len);
void uart_printf(const char *msg, ...);

const char *itox8(uint8_t x);
const char *itox32(uint32_t x);
