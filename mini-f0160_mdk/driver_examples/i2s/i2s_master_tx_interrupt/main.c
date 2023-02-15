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
#define SOUND_BUF_SIZE 16u

/*
 * Variables.
 */

/* The data of right channel to be transmitted. */
const int16_t sound_buf_right[SOUND_BUF_SIZE]  =
{
    0,  3827,  7071,  9238,  10000,  9238,  7071,  3827,
    0, -3827, -7071, -9238, -10000, -9238, -7071, -3827
};

/* The data of right channel to be transmitted. */
const int16_t sound_buf_left[SOUND_BUF_SIZE] =
{
    0, 3535, 5000, 3535, 0, -3535, -5000, -3535,
    0, 3535, 5000, 3535, 0, -3535, -5000, -3535,
};

/* Index of left channel data to be transmitted. */
uint32_t sound_buf_index_left  = 0u;

/* Index of right channel data to be transmitted. */
uint32_t sound_buf_index_right = 0u;

/*
 * Declerations.
 */
void app_i2s_master_init(void);
void app_i2s_put_data_left(void);
void app_i2s_put_data_right(void);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("i2s_master_interrupt.\r\n");

    app_i2s_master_init();

    while (1)
    {
    }
}

/* I2S master init. */
void app_i2s_master_init(void)
{
    I2S_Master_Init_Type i2s_master_init;
    i2s_master_init.ClockFreqHz  = BOARD_I2S_FREQ;
    i2s_master_init.SampleRate   = BOARD_I2S_SAMPLE_RATE;
    i2s_master_init.DataWidth    = BOARD_I2S_DATA_WIDTH;
    i2s_master_init.Protocol     = BOARD_I2S_PROTOCOL;
    i2s_master_init.EnableMCLK   = true;
    i2s_master_init.Polarity     = BOARD_I2S_CPOL;
    i2s_master_init.XferMode     = I2S_XferMode_TxOnly;

    I2S_InitMaster(BOARD_I2S_PORT, &i2s_master_init);

    /* Enable I2S tx buffer empty interrupt. */
    I2S_EnableInterrupts(BOARD_I2S_PORT, I2S_INT_TX_EMPTY, true);
    NVIC_EnableIRQ(BOARD_I2S_IRQn);

    I2S_Enable(BOARD_I2S_PORT, true);
}

/* Put data to left channel. */
void app_i2s_put_data_left(void)
{
    I2S_PutData(BOARD_I2S_PORT, (uint32_t)sound_buf_left[sound_buf_index_left]);
    sound_buf_index_left++;
    if (sound_buf_index_left >= SOUND_BUF_SIZE)
    {
        sound_buf_index_left = 0u;
    }
}

/* Put data to right channel. */
void app_i2s_put_data_right(void)
{
    I2S_PutData(BOARD_I2S_PORT, (uint32_t)sound_buf_right[sound_buf_index_right]);
    sound_buf_index_right++;
    if (sound_buf_index_right >= SOUND_BUF_SIZE)
    {
        sound_buf_index_right = 0u;
    }
}

/* I2S interrupt handler. */
void BOARD_I2S_IRQHandler(void)
{
    /* Get interrupt status. */
    uint32_t flag = I2S_GetInterruptStatus(BOARD_I2S_PORT);

    if (0u != (flag & I2S_INT_TX_EMPTY) )
    {
        if (I2S_Channel_Left != I2S_GetXferChannel(BOARD_I2S_PORT) )
        {
            app_i2s_put_data_left();  /* Send right data, buffer put left data to prepare next send. */
        }
        else
        {
            app_i2s_put_data_right(); /* Send left data, buffer put right data to prepare next send. */
        }
    }

    /* Clear interrupt status. */
    I2S_ClearInterruptStatus(BOARD_I2S_PORT, flag);
}

/* EOF. */
