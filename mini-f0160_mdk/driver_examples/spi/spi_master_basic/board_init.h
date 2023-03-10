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
#include "hal_spi.h"
#include "hal_dma.h"
#include "clock_init.h"
#include "pin_init.h"
#include "hal_dma_request.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ
#define BOARD_DEBUG_UART_IRQn        UART2_IRQn
#define BOARD_DEBUG_UART_IRQHandler  UART2_IRQHandler

#define BOARD_LOOP_SPI_PORT          SPI1
#define BOARD_LOOP_SPI_BAUDRATE      400000u /* 400khz. */
#define BOARD_LOOP_SPI_FREQ          CLOCK_APB2_FREQ

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
