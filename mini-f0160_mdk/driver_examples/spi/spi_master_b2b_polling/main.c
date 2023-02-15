/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

/*
 * Definitions.
 */
#define APP_SPI_BUF_LEN 16u /* SPI xfer buffer length. */

/*
 * Variables.
 */
uint8_t app_spi_tx_buf[APP_SPI_BUF_LEN]; /* Buffer for SPI Master tx. */
uint8_t app_spi_rx_buf[APP_SPI_BUF_LEN]; /* Buffer for SPI Master rx. */

/*
 * Declerations.
 */
void app_spi_init(void); /* Setup SPI Master. */
void app_spi_xfer(uint8_t * tx_buf, uint8_t * rx_buf, uint32_t len); /* SPI Master tx and rx block. */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    
    printf("spi_master_b2b_polling example.\r\n");
    
    /* Setup SPI Master. */
    app_spi_init();

    /* Prepare data. */
    for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; ++i)
    {
        app_spi_tx_buf[i] = i;
    }
    
    while (1)
    {
        getchar();
        
        /* Print sending data. */
        printf("\r\nspi send data:");
        for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; ++i)
        {
            printf("%u ", (unsigned)app_spi_tx_buf[i]);
        }
        printf("\r\n");
        
        /* SPI xfer. */
        app_spi_xfer(app_spi_tx_buf, app_spi_rx_buf, APP_SPI_BUF_LEN);
        
        /* Print and update xfer data. */
        printf("spi received data:");
        for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; ++i)
        {
            printf("%u ", (unsigned)app_spi_rx_buf[i]);
            app_spi_tx_buf[i] = (app_spi_tx_buf[i] + 1) % APP_SPI_BUF_LEN;
        }
        printf("\r\n");
    }
}

/* Setup SPI Master. */
void app_spi_init(void)
{
    /* Setup SPI Master. */
    SPI_Master_Init_Type spi_master_init;
    spi_master_init.ClockFreqHz = BOARD_MASTER_SPI_FREQ;
    spi_master_init.BaudRate = BOARD_MASTER_SPI_BAUDRATE;
    spi_master_init.XferMode = SPI_XferMode_TxRx;
    spi_master_init.PolPha = SPI_PolPha_Alt0;
    spi_master_init.DataWidth = SPI_DataWidth_8b;
    spi_master_init.LSB = false;
    spi_master_init.AutoCS = true; /* if set false, need SPI_EnableCS after spi enable. */
    SPI_InitMaster(BOARD_MASTER_SPI_PORT, &spi_master_init);
    
    /* Enable SPI Master. */
    SPI_Enable(BOARD_MASTER_SPI_PORT, true);
}

/* SPI xfer block. */
void app_spi_xfer(uint8_t * tx_buf, uint8_t * rx_buf, uint32_t len)
{
    for (uint32_t i = 0u; i < len; ++i)
    {
        /* Tx. */
        while ( SPI_STATUS_TX_FULL & SPI_GetStatus(BOARD_MASTER_SPI_PORT) )
        {}
        SPI_PutData(BOARD_MASTER_SPI_PORT, *tx_buf++);

        /* Rx. */
        while (0u == (SPI_STATUS_RX_DONE & SPI_GetStatus(BOARD_MASTER_SPI_PORT)) )
        {}
        *rx_buf = SPI_GetData(BOARD_MASTER_SPI_PORT);
        rx_buf++;
    }
}

/* EOF. */
