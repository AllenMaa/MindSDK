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
#include "hal_rcc.h"
#include "hal_uart.h"
#include "hal_dma.h"
#include "hal_dma_request.h"

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ
#define BOARD_DEBUG_UART_IRQn        UART2_IRQn
#define BOARD_DEBUG_UART_IRQHandler  UART2_IRQHandler

/* DMA for UART1. */
#define BOARD_DMA_UART_RX_PORT       DMA1
#define BOARD_DMA_UART_RX_CHANNEL    DMA_REQ_DMA1_UART2_RX_1
#define BOARD_DMA_UART_RX_IRQn       DMA1_CH7_CH4_IRQn
#define BOARD_DMA_UART_RX_IRQHandler DMA1_CH7_CH4_IRQHandler


void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
