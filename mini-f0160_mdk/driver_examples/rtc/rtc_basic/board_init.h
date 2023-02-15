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
#include "hal_gpio.h"
#include "hal_uart.h"

#include "clock_init.h"
#include "pin_init.h"


/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ

/* RTC */
#define BOARD_RTC_PORT               RTC
#define BOARD_RTC_IRQn               RTC_IRQn
#define BOARD_RTC_IRQ_HANDLER_FUNC   RTC_IRQHandler

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */

