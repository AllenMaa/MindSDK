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
#include "hal_gpio.h"
#include "hal_uart.h"

#include "clock_init.h"
#include "pin_init.h"

/* KEY1. */
#define BOARD_KEY0_GPIO_PORT         GPIOC
#define BOARD_KEY0_GPIO_PIN          GPIO_PIN_11

/* LED0. */
#define BOARD_LED0_GPIO_PORT         GPIOC
#define BOARD_LED0_GPIO_PIN          GPIO_PIN_9

/* LED1. */
#define BOARD_LED1_GPIO_PORT         GPIOC
#define BOARD_LED1_GPIO_PIN          GPIO_PIN_8

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */

