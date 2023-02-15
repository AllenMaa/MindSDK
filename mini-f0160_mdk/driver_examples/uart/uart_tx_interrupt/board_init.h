/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __BOARD_INIT_H__
#define __BOARD_INIT_H__

#include <stdio.h>

#include "hal_common.h"

#include "clock_init.h"

#define BOARD_LED_GPIO_PORT  (GPIOC)
#define BOARD_LED_GPIO_PINS  (GPIO_PIN_9)

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ
#define BOARD_DEBUG_UART_IRQn        UART2_IRQn
#define BOARD_DEBUG_UART_IRQHandler  UART2_IRQHandler

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
