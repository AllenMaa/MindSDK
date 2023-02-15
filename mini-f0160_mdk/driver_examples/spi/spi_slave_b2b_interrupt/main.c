/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

/*
 * Variables.
 */
volatile uint32_t app_spi_xfer_cnt; /* SPI Slave xfer cnt value. */

/*
 * Declerations.
 */
void app_spi_init(void); /* Setup SPI Slave. */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("spi_slave_b2b_interrupt example.\r\n");

    /* Setup SPI Slave. */
    app_spi_init();
    
    while (1)
    {
        getchar();

        /* print interrupt counter. */
        printf("\r\nspi slave interrupt count:%u.\r\n",(unsigned)app_spi_xfer_cnt);
    }
}

/* Setup SPI Slave. */
void app_spi_init(void)
{
    /* Initiate SPI Slave node. */
    SPI_Slave_Init_Type spi_slave_init;
    spi_slave_init.XferMode = SPI_XferMode_TxRx;
    spi_slave_init.PolPha = SPI_PolPha_Alt0;
    spi_slave_init.DataWidth = SPI_DataWidth_8b;
    spi_slave_init.LSB = false;
    spi_slave_init.AutoCS = true;
    SPI_InitSlave(BOARD_SLAVE_SPI_PORT, &spi_slave_init);

    /* Enable RX interrupt. */
    SPI_EnableInterrupts(BOARD_SLAVE_SPI_PORT, SPI_INT_RX_DONE, true);
    NVIC_EnableIRQ(BOARD_SLAVE_SPI_IRQn);

    /* Enable SPI module. */
    SPI_Enable(BOARD_SLAVE_SPI_PORT, true);
}

/* SPI Slave IRQ. */
void BOARD_SLAVE_SPI_IRQHandler(void)
{
    uint32_t flags = SPI_GetInterruptStatus(BOARD_SLAVE_SPI_PORT);
    if ( 0u != (flags & SPI_INT_RX_DONE ) ) /* Check Rx done status. */
    {
        /* Update counter. */
        app_spi_xfer_cnt++;
        SPI_PutData(BOARD_SLAVE_SPI_PORT, SPI_GetData(BOARD_SLAVE_SPI_PORT));
    }
    SPI_ClearInterruptStatus(BOARD_SLAVE_SPI_PORT, flags);
}

/* EOF. */

