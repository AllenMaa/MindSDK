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

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT           UART2
#define BOARD_DEBUG_UART_BAUDRATE       9600u
#define BOARD_DEBUG_UART_FREQ           CLOCK_APB1_FREQ

/* FLEXCAN. */
#define BOARD_FLEXCAN_PORT              FLEXCAN
#define BOARD_FLEXCAN_CLOCK_FREQ        CLOCK_PLL1_FREQ
#define BOARD_FLEXCAN_TX_MB_CH          0u
#define BOARD_FLEXCAN_TX_MB_INT         FLEXCAN_INT_MB_0
#define BOARD_FLEXCAN_IRQHandler        FLEXCAN_IRQHandler
#define BOARD_FLEXCAN_TX_MB_STATUS      FLEXCAN_STATUS_MB_0
#define BOARD_FLEXCAN_IRQn              FlexCAN_IRQn

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
