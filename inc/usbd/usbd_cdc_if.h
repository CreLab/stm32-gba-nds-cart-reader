/**
 ******************************************************************************
 * @file           : usbd_cdc_if.h
 * @version        : v2.0_Cube
 * @brief          : Header for usbd_cdc_if.c file.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef __USBD_CDC_IF_H__
#define __USBD_CDC_IF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lib/usbd_lib/inc/usbd_cdc.h"

#define APP_RX_DATA_SIZE 1024
#define APP_TX_DATA_SIZE 1024

extern USBD_CDC_ItfTypeDef USBD_Interface_fops_FS;
extern uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
extern uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

uint8_t CDC_Transmit_FS(uint8_t *Buf, uint16_t Len);

#ifdef __cplusplus
}
#endif

#endif /* __USBD_CDC_IF_H__ */
