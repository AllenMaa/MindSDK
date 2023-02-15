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
#define APP_SPI_BUF_LEN 16u /* Xfer buffer length. */
#define SPI_DUMMY_BYTE 0xff

/* SPI transfer done callback type. */
typedef void(*spi_xfer_callback_t)(void * param);

/* SPI transfer handler type. */
typedef struct
{
    SPI_Type * spi_if; /* SPI hardware interface. */
    uint8_t * tx_buf;  /* SPI handler tx buffer. */
    uint8_t * rx_buf;  /* SPI handler rx buffer. */
    uint32_t buf_len; /* SPI handler buffer length. */
    uint32_t tx_idx;  /* Index of counter for current tx buffer. */
    uint32_t rx_idx;  /* Index of counter for current rx buffer. */
    spi_xfer_callback_t rx_done_callback; /* Callback function for rx done calling. */
} spi_xfer_handler_t;

/*
 * Variables.
 */
uint8_t spi_tx_buf[APP_SPI_BUF_LEN]; /* Buffer for master tx. */
uint8_t spi_rx_buf[APP_SPI_BUF_LEN]; /* Buffer for master rx. */
spi_xfer_handler_t spi_xfer_handler; /* SPI transfer handler. */
volatile bool app_spi_xfer_flag; /* SPI xfer status. */

/*
 * Declerations.
 */
void spi_init(spi_xfer_handler_t * handler, SPI_Type * spi_if); /* Setup SPI master. */
bool spi_xfer(spi_xfer_handler_t * handler, uint8_t * tx_buf, uint8_t * rx_buf, uint32_t buf_len, spi_xfer_callback_t callback); /* SPI master tx and rx block. */
void spi_rx_done_callback(void * param); /* SPI rx done callback function. */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("spi_master_b2b_interrupt example.\r\n");

    /* Setup SPI master. */
    spi_init(&spi_xfer_handler, BOARD_MASTER_SPI_PORT);

    /* Prepare the data. */
    for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; ++i)
    {
        spi_tx_buf[i] = i;
    }

    while (1)
    {
        getchar();

        /* tx. */
        printf("spi tx data:");
        for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; ++i)
        {
            printf("%u ", (unsigned)spi_tx_buf[i]);
        }
        printf("\r\n");

        spi_xfer(&spi_xfer_handler, spi_tx_buf, spi_rx_buf, APP_SPI_BUF_LEN, spi_rx_done_callback);
        while (!app_spi_xfer_flag)
        {
        }
        app_spi_xfer_flag = false;

        /* rx. */
        printf("spi rx data:");
        for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; ++i)
        {
            printf("%u ", (unsigned)spi_rx_buf[i]);
        }
        printf("\r\n\r\n");

        /* update tx data. */
        for (uint32_t i = 0u; i < APP_SPI_BUF_LEN; ++i)
        {
            spi_tx_buf[i] = (spi_tx_buf[i] + 1u) % APP_SPI_BUF_LEN;
        }
    }
}

/* Callback when SPI rx done. */
void spi_rx_done_callback(void * param)
{
    spi_xfer_handler_t * handler = (spi_xfer_handler_t *) param;
    printf("spi xfer len: %u\r\n", (unsigned)(handler->buf_len));
    app_spi_xfer_flag = true;
}

/* Setup SPI. */
void spi_init(spi_xfer_handler_t * handler, SPI_Type * spi_if)
{
    /* Enable NVIC for SPI. */
    NVIC_EnableIRQ(BOARD_MASTER_SPI_IRQn);

    /* Setup SPI master. */
    SPI_Master_Init_Type spi_master_init;
    spi_master_init.ClockFreqHz = BOARD_MASTER_SPI_FREQ;
    spi_master_init.BaudRate = BOARD_MASTER_SPI_BAUDRATE;
    spi_master_init.XferMode = SPI_XferMode_TxRx;
    spi_master_init.PolPha = SPI_PolPha_Alt0;
    spi_master_init.DataWidth = SPI_DataWidth_8b;
    spi_master_init.LSB = false;
    spi_master_init.AutoCS = true; /* if set false, need SPI_EnableCS after spi enable. */
    SPI_InitMaster(spi_if, &spi_master_init);
    SPI_Enable(spi_if, true);

    handler->spi_if = spi_if;
}

/* SPI xfer data block. */
bool spi_xfer(spi_xfer_handler_t * handler, uint8_t * tx_buf, uint8_t * rx_buf, uint32_t buf_len, spi_xfer_callback_t callback)
{
    /* Check parameters. */
    if ( ( (rx_buf == NULL) && (tx_buf == NULL) ) || buf_len == 0u)
    {
        return false;
    }

    /* Prepare handler. */
    handler->tx_buf = tx_buf;
    handler->rx_buf = rx_buf;
    handler->buf_len = buf_len;
    handler->tx_idx = 0u;
    handler->rx_idx = 0u;
    handler->rx_done_callback = callback;

    /* Enable the interrupts to start transfer. */
    SPI_EnableInterrupts(handler->spi_if, SPI_INT_TX_DONE | SPI_INT_RX_DONE, true);

    return true;
}

/* xfer handler called by hardware ISR. */
void spi_master_xfer_handler(spi_xfer_handler_t * handler, uint32_t flags)
{
    /* rx. */
    if ( 0u != (flags & SPI_INT_RX_DONE) )
    {
        if (handler->rx_idx < handler->buf_len)
        {
            uint8_t rx_data = SPI_GetData(handler->spi_if);
            if (handler->rx_buf != NULL)
            {
                handler->rx_buf[handler->rx_idx] = rx_data;
            }
            handler->rx_idx++;
        }
        if (handler->rx_idx >= handler->buf_len)
        {
            SPI_EnableInterrupts(handler->spi_if, SPI_INT_RX_DONE, false);
            if (handler->rx_done_callback)
            {
                handler->rx_done_callback((void*)handler);
            }
        }
    }

    /* tx. */
    if ( 0u != (flags & SPI_INT_TX_DONE ) )
    {
        if (handler->tx_idx < handler->buf_len)
        {
            if (handler->tx_buf != NULL)
            {
                SPI_PutData(handler->spi_if, handler->tx_buf[handler->tx_idx]);
            }
            else
            {
                SPI_PutData(handler->spi_if, SPI_DUMMY_BYTE);
            }
            handler->tx_idx++;
        }
        else
        {
            SPI_EnableInterrupts(handler->spi_if, SPI_INT_TX_DONE, false);
        }
    }
}

/* SPI master IRQ. */
void BOARD_MASTER_SPI_IRQHandler(void)
{
    /* Get status of enabled interrupts. */
    uint32_t flags = ( SPI_GetInterruptStatus(spi_xfer_handler.spi_if) & SPI_GetEnabledInterrupts(spi_xfer_handler.spi_if) );

    spi_master_xfer_handler(&spi_xfer_handler, flags);

    /* Clear interrupt flags. */
    SPI_ClearInterruptStatus(spi_xfer_handler.spi_if, flags);
}

/* EOF. */

