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

/* USB. */
#define BOARD_USB_PORT               USB
#define BOARD_USB_IRQn               USB_IRQn
#define BOARD_USB_IRQHandler         USB_IRQHandler

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
