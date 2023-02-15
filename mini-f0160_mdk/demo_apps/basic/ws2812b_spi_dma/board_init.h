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
#include "hal_dma_request.h"

#include "clock_init.h"
#include "pin_init.h"

/* DEBUG UART. */
#define BOARD_DEBUG_UART_PORT        UART2
#define BOARD_DEBUG_UART_BAUDRATE    9600u
#define BOARD_DEBUG_UART_FREQ        CLOCK_APB1_FREQ

#define WS2812B_LIST_LED_NUM   8u
#define WS2812B_DISP_PIXEL_LEN 24u /* 24bit.  */
#define WS2812B_DISP_BUFF_LEN  (WS2812B_DISP_PIXEL_LEN * WS2812B_LIST_LED_NUM)

#define WS2812B_SPI_TX_PORT            SPI1
#define WS2812B_SPI_TX_FREQ            CLOCK_APB2_FREQ
#define WS2812B_SPI_TX_BAUDRATE        6400000u  /* 6.4Mbps */

#define WS2812B_SPI_TX_DMA_PORT        DMA1
#define WS2812B_SPI_TX_DMA_CHANNEL     DMA_REQ_DMA1_SPI1_TX
#define WS2812B_SPI_TX_DMA_IRQ         DMA1_CH3_CH2_IRQn
#define WS2812B_SPI_TX_DMA_IRQHandler  DMA1_CH3_CH2_IRQHandler

#define WS2812B_BIT0_CODE              0xC0
#define WS2812B_BIT1_CODE              0xF0

#define WS2812B_COLOR_GREEN   0xFF0000
#define WS2812B_COLOR_RED     0xFF00
#define WS2812B_COLOR_BLUE    0xFF

void BOARD_Init(void);

void ws2812b_init(void);
void ws2812b_display_set_color(uint32_t color, uint32_t index);
void ws2812b_display_clear_color(void);
void ws2812b_display_buff_update_all(void);
void ws2812b_display_start(void);
void ws2812b_display_waitdone(void);

#endif /* __BOARD_INIT_H__ */
