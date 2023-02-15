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
#define SOUND_BUF_SIZE 16u  /* I2S buffer for I2S tx. */

/*
 * Variables.
 */

/* i2s left channel xfer data. */
const int16_t sound_buf_left[SOUND_BUF_SIZE] =
{
    0, 3535, 5000, 3535, 0, -3535, -5000, -3535,
    0, 3535, 5000, 3535, 0, -3535, -5000, -3535,
};

/* i2s right channel xfer data. */
const int16_t sound_buf_right[SOUND_BUF_SIZE] =
{
    0,  3827,  7071,  9238,  10000,  9238,  7071,  3827,
    0, -3827, -7071, -9238, -10000, -9238, -7071, -3827
};

/* i2s xfer data index. */
uint32_t sound_buf_index_left  = 0;
uint32_t sound_buf_index_right = 0;

/*
 * Declerations.
 */
void app_i2s_master_init(void);     /* Setup I2S master module. */
void app_i2s_put_data_left(void);   /* I2S left channel data.  */
void app_i2s_put_data_right(void);  /* I2S right channel data. */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("i2s_master_basic.\r\n");

    app_i2s_master_init();

    while (1)
    {
        while(0u != (I2S_GetStatus(BOARD_I2S_PORT) & SPI_I2S_CSTAT_TXFULL_MASK) )
        {}
            
        app_i2s_put_data_left(); /* sending left channel data. */

        while(0u != (I2S_GetStatus(BOARD_I2S_PORT) & SPI_I2S_CSTAT_TXFULL_MASK) )
        {}
        app_i2s_put_data_right(); /* sending right channel data. */
    }
}

/* setup I2S. */
void app_i2s_master_init(void)
{
    /* setup I2S master module. */
    I2S_Master_Init_Type i2s_master_init;

    i2s_master_init.ClockFreqHz  = BOARD_I2S_FREQ;
    i2s_master_init.SampleRate   = BOARD_I2S_SAMPLE_RATE;
    i2s_master_init.DataWidth    = BOARD_I2S_DATA_WIDTH;
    i2s_master_init.Protocol     = BOARD_I2S_PROTOCOL;
    i2s_master_init.EnableMCLK   = true;
    i2s_master_init.Polarity     = BOARD_I2S_CPOL;
    i2s_master_init.XferMode     = I2S_XferMode_TxOnly;

    I2S_InitMaster(BOARD_I2S_PORT, &i2s_master_init);

    /* enable I2S. */
    I2S_Enable(BOARD_I2S_PORT, true);
}

/* put data into left channel. */
void app_i2s_put_data_left(void)
{
    I2S_PutData(BOARD_I2S_PORT, (uint32_t)sound_buf_left[sound_buf_index_left]);
    sound_buf_index_left++;
    if (sound_buf_index_left >= SOUND_BUF_SIZE)
    {
        sound_buf_index_left = 0;
    }
}

/* put data into right channel. */
void app_i2s_put_data_right(void)
{
    I2S_PutData(BOARD_I2S_PORT, (uint32_t)sound_buf_right[sound_buf_index_right]);
    sound_buf_index_right++;
    if (sound_buf_index_right >= SOUND_BUF_SIZE)
    {
        sound_buf_index_right = 0;
    }
}

/* EOF. */
