/*
 * Copyright 2022 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"

/*
 * Macros.
 */

#define APP_DMA_BUFF_COUNT (16u * 2u)  /* Xfer buffer length. */

/*
 * Variables.
 */
int16_t sound_buf[APP_DMA_BUFF_COUNT] = 
{
/* left   right */
    0,      0,
    3535,   3827,
    5000,   7071,
    3535,   9238,
    0,      10000,
    -3535,  9238,
    -5000,  7071,
    -3535,  3827,
    0,      0,
    3535,   -3827,
    5000,   -7071,
    3535,   -9238,
    0,      -10000,
    -3535,  -9238,
    -5000,  -7071,
    -3535,  -3827,
};

/*
 * Declerations.
 */
void app_i2s_master_tx_dma_init(void);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("i2s_master_dma.\r\n");
    
    app_i2s_master_tx_dma_init();

    while (1)
    {
    }
}

void app_i2s_master_tx_dma_init(void)
{
    /* Setup the DMA for I2S RX. */
    DMA_Channel_Init_Type dma_channel_init;

    dma_channel_init.MemAddr           = (uint32_t)(sound_buf);
    dma_channel_init.MemAddrIncMode    = DMA_AddrIncMode_IncAfterXfer;
    dma_channel_init.PeriphAddr        = I2S_GetTxDataRegAddr(BOARD_I2S_PORT);  /* use tx data register here. */
    dma_channel_init.PeriphAddrIncMode = DMA_AddrIncMode_StayAfterXfer;
    dma_channel_init.Priority          = DMA_Priority_Low;
    dma_channel_init.XferCount         = APP_DMA_BUFF_COUNT;
    dma_channel_init.XferMode          = DMA_XferMode_MemoryToPeriph;
    dma_channel_init.ReloadMode        = DMA_ReloadMode_AutoReload;             /* DMA_AutoReloadMode_Circular */
    dma_channel_init.XferWidth         = DMA_XferWidth_16b;
    DMA_InitChannel(BOARD_DMA_I2S_PORT, BOARD_DMA_I2S_CHN, &dma_channel_init);

    /* Enable DMA transfer done interrupt. */
    DMA_EnableChannelInterrupts(BOARD_DMA_I2S_PORT, BOARD_DMA_I2S_CHN, DMA_CHN_INT_XFER_DONE, true);
    NVIC_EnableIRQ(BOARD_DMA_I2S_IRQn);

    /* Setup the I2S. */
    I2S_Master_Init_Type i2s_master_init;

    i2s_master_init.ClockFreqHz  = BOARD_I2S_FREQ;
    i2s_master_init.SampleRate   = BOARD_I2S_SAMPLE_RATE;
    i2s_master_init.DataWidth    = BOARD_I2S_DATA_WIDTH;
    i2s_master_init.Protocol     = BOARD_I2S_PROTOCOL;
    i2s_master_init.EnableMCLK   = true;
    i2s_master_init.Polarity     = BOARD_I2S_CPOL;
    i2s_master_init.XferMode     = I2S_XferMode_TxOnly;

    I2S_InitMaster(BOARD_I2S_PORT, &i2s_master_init);

    I2S_EnableDMA(BOARD_I2S_PORT, true);

    I2S_Enable(BOARD_I2S_PORT, true);

    DMA_EnableChannel(BOARD_DMA_I2S_PORT, BOARD_DMA_I2S_CHN, true);
}

/* I2S IRQ. */
void BOARD_DMA_I2S_IRQHandler(void)
{
    if (0u != (DMA_GetChannelInterruptStatus(BOARD_DMA_I2S_PORT, BOARD_DMA_I2S_CHN) & DMA_CHN_INT_XFER_DONE) )
    {
        DMA_EnableChannel(BOARD_DMA_I2S_PORT, BOARD_DMA_I2S_CHN, true);
        DMA_ClearChannelInterruptStatus(BOARD_DMA_I2S_PORT, BOARD_DMA_I2S_CHN, DMA_CHN_INT_XFER_DONE);
    }
}

/* EOF. */
