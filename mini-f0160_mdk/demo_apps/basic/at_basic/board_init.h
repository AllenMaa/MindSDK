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
#include "hal_rcc.h"
#include "hal_uart.h"
#include "hal_gpio.h"

#include "clock_init.h"
#include "pin_init.h"

#include "rbuf.h"
#include "at_server.h"

/* DEBUG UART. */
#define BOARD_AT_UART_PORT        UART2
#define BOARD_AT_UART_BAUDRATE    9600u
#define BOARD_AT_UART_FREQ        CLOCK_APB1_FREQ

#define BOARD_AT_UART_IRQn       UART2_IRQn
#define BOARD_AT_UART_IRQHandler UART2_IRQHandler

/* LED. */
#define BOARD_LED0_GPIO_PORT GPIOC
#define BOARD_LED0_GPIO_PIN  GPIO_PIN_9

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
