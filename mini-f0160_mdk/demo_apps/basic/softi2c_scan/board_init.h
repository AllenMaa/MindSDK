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

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ

/* SOFTI2C GPIO. */
#define BOARD_SOFTI2C_SCL_GPIO_PORT  GPIOB
#define BOARD_SOFTI2C_SCL_GPIO_PIN   GPIO_PIN_10
#define BOARD_SOFTI2C_SDA_GPIO_PORT  GPIOB
#define BOARD_SOFTI2C_SDA_GPIO_PIN   GPIO_PIN_11

#define BOARD_SOFTI2C_BPSDELAY       50
#define BOARD_SOFTI2C_TIMEOUT_DELAY  100

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */

