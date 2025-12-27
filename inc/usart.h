#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

GLOBAL_STATUS MX_USART1_UART_Init(void);
UART_HandleTypeDef* Get_USART1_UART_Handle(void);

#ifdef __cplusplus
}
#endif

#endif /*__USART_H */
