#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

extern UART_HandleTypeDef huart1;

GLOBAL_STATUS MX_USART1_UART_Init(void);

#ifdef __cplusplus
}
#endif

#endif /*__USART_H */
