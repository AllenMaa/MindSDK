/*
 * Copyright 2023 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "hal_flexcan.h"

/*
 * Macros.
 */
#define APP_FLEXCAN_XFER_BITRATE   1000000u /* The flexcan nominal bitrate = 1 Mbps. */
#define APP_FLEXCAN_XFER_FDBITRATE 2000000u /* The flexcan data bitrate = 2 Mbps. */
#define APP_FLEXCAN_XFER_MaxNum    15u      /* Amount of mb to be used. */
#define APP_FLEXCAN_XFER_ID        0x666u   /* The flexcan xfer Id number. */
#define APP_FLEXCAN_XFER_BUF_LEN   16u      /* The flexcan xfer buffer length. */

/*
 * Variables.
 */
volatile bool app_flexcan_tx_flag = false; /* Flag the message buffer transport state. */
uint8_t app_flexcan_tx_buf[APP_FLEXCAN_XFER_BUF_LEN]; /* The flexcan tx buffer for tx mb frame preparation. */

/*
 * Declerations.
 */
void app_flexcan_init(void); /* Setup flexcan with fd. */
void app_flexcan_tx(uint8_t *tx_buf); /* Transport frame. */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("\r\nflexcan_fd_b2b_tx example.\r\n");

    /* Setup the flexcan with fd module.*/
    app_flexcan_init();

    while (1)
    {
        /* Send a message through flexcan. */
        printf("app_flexcan_tx() sending: ");
        for (uint8_t i = 0u; i < APP_FLEXCAN_XFER_BUF_LEN; i++)
        {
            app_flexcan_tx_buf[i] = app_flexcan_tx_buf[i]+i;
            printf("%X ", (unsigned)app_flexcan_tx_buf[i]);
        }
        printf("\r\n");
        app_flexcan_tx(app_flexcan_tx_buf);

        /* Wait for reception. */
        while (!app_flexcan_tx_flag) /* This flag will be on when the Tx interrupt is asserted. */
        {
        }
        app_flexcan_tx_flag = false;
        printf("app_flexcan_tx() done.\r\n\r\n");

        getchar();
    }
}

/* Set up the flexCAN with fd module. */
void app_flexcan_init(void)
{
    /* Set bit timing. */
    FLEXCAN_TimConf_Type flexcan_tim_conf;
    flexcan_tim_conf.EnableExtendedTime = true;
    flexcan_tim_conf.PhaSegLen1 = 5u;
    flexcan_tim_conf.PhaSegLen2 = 1u;
    flexcan_tim_conf.PropSegLen = 2u;
    flexcan_tim_conf.JumpWidth = 1u;

    /* Setup FlexCAN. */
    FLEXCAN_Init_Type flexcan_init;
    flexcan_init.MaxXferNum = APP_FLEXCAN_XFER_MaxNum; /* The max amount of mbs to be used. */
    flexcan_init.ClockSource = FLEXCAN_ClockSource_Periph; /* Use peripheral clock. */
    flexcan_init.BitRate = APP_FLEXCAN_XFER_BITRATE; /* Set nominal bitrate. */
    flexcan_init.ClockFreqHz = BOARD_FLEXCAN_CLOCK_FREQ; /* Set clock frequency. */
    flexcan_init.SelfWakeUp = FLEXCAN_SelfWakeUp_BypassFilter; /* Use unfiltered signal to wake up flexcan. */
    flexcan_init.WorkMode = FLEXCAN_WorkMode_Normal; /* Normal workmode, can receive and transport. */
    flexcan_init.Mask = FLEXCAN_Mask_Global; /* Use global mask for filtering. */
    flexcan_init.EnableSelfReception = false; /* Not receiving mb frame sent by self. */
    flexcan_init.EnableTimerSync = true; /* Every tx or rx done, refresh the timer to start from zero. */
    flexcan_init.TimConf = &flexcan_tim_conf; /* Set timing sychronization. */
    FLEXCAN_Init(BOARD_FLEXCAN_PORT, &flexcan_init);

    /* Set date bitrate. */
    FLEXCAN_FdBitRateConf_Type fd_bitrate_conf;
    fd_bitrate_conf.FdBitRate = APP_FLEXCAN_XFER_FDBITRATE; /* Set data bitrate. */
    fd_bitrate_conf.ClockFreqHz= BOARD_FLEXCAN_CLOCK_FREQ; /* Set clock frequency. */
    fd_bitrate_conf.TimConf = &flexcan_tim_conf; /* Set data timing sychronization. */
    fd_bitrate_conf.EnableFdRate = true;  /* Enable flexcan data bitrate. */

    /* Setup FlexCAN FD. */
    FLEXCAN_InitFd_Type flexcan_init_fd;
    flexcan_init_fd.FdBitRateConf = &fd_bitrate_conf;
    flexcan_init_fd.MbSize = FLEXCAN_MbSize_16Bytes;
    flexcan_init_fd.EnableIsoCanFd = true;
    FLEXCAN_InitFd(BOARD_FLEXCAN_PORT, &flexcan_init_fd);

    /* Set tx mb. */
    FLEXCAN_ResetFdMb(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH);
    FLEXCAN_SetFdMbCode(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH, FLEXCAN_MbCode_TxInactive);

    /* Enable intterupts for tx mb. */
    FLEXCAN_EnableMbInterrupts(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_INT, true);
    NVIC_EnableIRQ(BOARD_FLEXCAN_IRQn);
}

/* Interrupt request handler. */
void BOARD_FLEXCAN_IRQHandler(void)
{
    if ( 0u != (FLEXCAN_GetMbStatus(BOARD_FLEXCAN_PORT) & BOARD_FLEXCAN_TX_MB_STATUS) )
    {
        /* Clear flag. */
        FLEXCAN_ClearMbStatus(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_STATUS);
        /* Update the flag. */
        app_flexcan_tx_flag = true;
    }
}

/* Send a message frame. */
void app_flexcan_tx(uint8_t * tx_buf)
{
    FLEXCAN_FdMb_Type mb;
    mb.ID = APP_FLEXCAN_XFER_ID; /* Indicated ID number. */
    mb.TYPE = FLEXCAN_MbType_Data; /* Data frame type. */
    mb.FORMAT = FLEXCAN_MbFormat_Standard; /* STD frame format. */
    mb.BRS = true; /* bit rate switch*/
    mb.EDL = true; /* externd date length . */

    /* Set the information. */
    for (uint32_t i = 0; i < 4u; i++)
    {
        mb.WORD[i] = tx_buf[i*4]<<24|tx_buf[i*4+1]<<16|tx_buf[i*4+2]<<8|tx_buf[i*4+3];
    }

    /* Set the Data size. */
    mb.LENGTH = FLEXCAN_DataLen_16Bytes;

    /* Send. */
    FLEXCAN_WriteFdTxMb(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH, &mb);
    FLEXCAN_SetFdMbCode(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH, FLEXCAN_MbCode_TxDataOrRemote); /* Write code to send. */
}
/* EOF. */
