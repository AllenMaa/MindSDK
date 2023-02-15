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
#include "hal_i2s.h"
#include "hal_dma.h"
#include "hal_dma_request.h"

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ

/* I2S. */
#define BOARD_I2S_PORT               SPI2
#define BOARD_I2S_FREQ               CLOCK_APB1_FREQ
#define BOARD_I2S_SAMPLE_RATE        8000u
#define BOARD_I2S_DATA_WIDTH         I2S_DataWidth_16b
#define BOARD_I2S_PROTOCOL           I2S_Protocol_PHILIPS
#define BOARD_I2S_CPOL               I2S_Polarity_1
#define BOARD_I2S_IRQHandler         SPI2_IRQHandler
#define BOARD_I2S_IRQn               SPI2_IRQn

/* DMA. */
#define BOARD_DMA_I2S_PORT           DMA1
#define BOARD_DMA_I2S_CHN            DMA_REQ_DMA1_SPI2_TX_1
#define BOARD_DMA_I2S_IRQHandler     DMA1_CH7_CH4_IRQHandler
#define BOARD_DMA_I2S_IRQn           DMA1_CH7_CH4_IRQn

void BOARD_Init(void);

#endif /* __BOARD_INIT_H__ */
