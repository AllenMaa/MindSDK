/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef __BOARD_INIT_H__
#define __BOARD_INIT_H__

#include <stdio.h>
#include <stdint.h>

#include "hal_common.h"

#include "clock_init.h"

/* LED. */
#define BOARD_LED0_GPIO_PORT GPIOC
#define BOARD_LED0_GPIO_PIN  GPIO_PIN_9

/* DEBUG UART. */
/* DEBUG LPUART. */
#define BOARD_DEBUG_LPUART_PORT        LPUART
#define BOARD_DEBUG_LPUART_BAUDRATE    LPUART_Baudrate_9600
#define BOARD_DEBUG_LPUART_IRQn        LPUART_IRQn
#define BOARD_DEBUG_LPUART_IRQHandler  LPUART_IRQHandler

void BOARD_Init(void);
void BOARD_LedOn(void);
void BOARD_LedOff(void);

#endif /* __BOARD_INIT_H__ */

