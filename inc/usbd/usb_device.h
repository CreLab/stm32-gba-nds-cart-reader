/**
 ******************************************************************************
 * @file           : usb_device.h
 * @version        : v2.0_Cube
 * @brief          : Header for usb_device.c file.
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

#ifndef __USB_DEVICE__H__
#define __USB_DEVICE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "usbd_def.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "util.h"

GLOBAL_STATUS MX_USB_DEVICE_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEVICE__H__ */
