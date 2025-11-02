#ifndef GPIOS_H
#define GPIOS_H

#include "util.h"

void clk_low(void);
void clk_high(void);
void romcs_low(void);
void romcs_high(void);
void reset_low(void);
void reset_high(void);
void eepromcs_low(void);
void eepromcs_high(void);
void data_dir_input(void);
uint8_t data_input(void);
void data_dir_output(void);
void data_output(uint8_t v);

#endif // GPIOS_H
