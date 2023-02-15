/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "hal_flexcan.h"

/*
 * Macros.
 */
#define APP_FLEXCAN_XFER_BITRATE   1000000u /* The flexcan bitrate = 1 Mbps. */
#define APP_FLEXCAN_XFER_MaxNum    15u      /* Amount of mb to be used. */
#define APP_FLEXCAN_XFER_ID        0x666u   /* The flexcan xfer Id number. */
#define APP_FLEXCAN_XFER_BUF_LEN   8u       /* The flexcan xfer buffer length. */

/*
 * Variables.
 */
volatile bool app_flexcan_rx_flag = false; /* Flag the message buffer reception state. */

FLEXCAN_Mb_Type app_flexcan_rx_mb; /* For message buffer rx frame storage. */
uint8_t app_flexcan_rx_buf[APP_FLEXCAN_XFER_BUF_LEN]; /* The flexcan rx buffer for rx mb frame storage. */

/*
 * Declerations.
 */
void app_flexcan_init(void); /* Setup flexcan. */
void app_flexcan_read(uint8_t *rx_buf); /* Receive frame. */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("\r\nflexcan_b2b_rx example.\r\n");

    /* Setup the flexcan module.*/
    app_flexcan_init();
    printf("waiting for frame with id 0x%x ...\r\n", (unsigned)APP_FLEXCAN_XFER_ID);

    while (1)
    {
        /* Wait for reception. */
        while (!app_flexcan_rx_flag) /* This flag will be on when the Rx interrupt is asserted. */
        {
        }
        app_flexcan_rx_flag = false;

        printf("app_flexcan_read() at timestamp %u with id 0x%x: ", (unsigned)app_flexcan_rx_mb.TIMESTAMP, (unsigned)app_flexcan_rx_mb.ID);
        for (uint8_t i = 0u; i<APP_FLEXCAN_XFER_BUF_LEN; i++)
        {
            printf("%u ", (unsigned)app_flexcan_rx_buf[i]);
        }
        printf("\r\n\r\n");
    }
}

/* Set up the flexCAN module. */
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
    flexcan_init.BitRate = APP_FLEXCAN_XFER_BITRATE; /* Set bitrate. */
    flexcan_init.ClockFreqHz = BOARD_FLEXCAN_CLOCK_FREQ; /* Set clock frequency. */
    flexcan_init.SelfWakeUp = FLEXCAN_SelfWakeUp_BypassFilter; /* Use unfiltered signal to wake up flexcan. */
    flexcan_init.WorkMode = FLEXCAN_WorkMode_Normal; /* Normal workmode, can receive and transport. */
    flexcan_init.Mask = FLEXCAN_Mask_Global; /* Use global mask for filtering. */
    flexcan_init.EnableSelfReception = false; /* Not receiving mb frame sent by self. */
    flexcan_init.EnableTimerSync = true; /* Every tx or rx done, refresh the timer to start from zero. */
    flexcan_init.TimConf = &flexcan_tim_conf; /* Set timing sychronization. */
    FLEXCAN_Init(BOARD_FLEXCAN_PORT, &flexcan_init);

    /* Set rx mb. */
    FLEXCAN_RxMbConf_Type flexcan_mb_conf;
    flexcan_mb_conf.Id = APP_FLEXCAN_XFER_ID; /* Id for filtering with mask and receiving. */
    flexcan_mb_conf.MbType = FLEXCAN_MbType_Data; /* Only receive standard data frame. */
    flexcan_mb_conf.MbFormat = FLEXCAN_MbFormat_Standard;
    FLEXCAN_SetRxMb(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_RX_MB_CH, &flexcan_mb_conf);
    FLEXCAN_SetMbCode(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_RX_MB_CH, FLEXCAN_MbCode_RxEmpty); /* Set for receiving. */

    /* Enable intterupts for rx mb. */
    FLEXCAN_EnableMbInterrupts(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_RX_MB_INT, true);
    NVIC_EnableIRQ(BOARD_FLEXCAN_IRQn);
}

/* Interrupt request handler. */
void BOARD_FLEXCAN_IRQHandler(void)
{
    /* Judge the xfer event. */
    if (0u!= (FLEXCAN_GetMbStatus(BOARD_FLEXCAN_PORT) & BOARD_FLEXCAN_RX_MB_STATUS) )
    {
        /* Read the message. */
        app_flexcan_read(app_flexcan_rx_buf);

        /* Clear flexcan mb interrupt flag. */
        FLEXCAN_ClearMbStatus(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_RX_MB_STATUS);
        /* Update the flag. */
        app_flexcan_rx_flag = true;
    }
}

/* Receive a message frame. */
void app_flexcan_read(uint8_t *rx_buf)
{
    /* Read the info from mb and reconstruct for understanding. */
    FLEXCAN_ReadRxMb(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_RX_MB_CH, &app_flexcan_rx_mb);
    rx_buf[0] = app_flexcan_rx_mb.BYTE0;
    rx_buf[1] = app_flexcan_rx_mb.BYTE1;
    rx_buf[2] = app_flexcan_rx_mb.BYTE2;
    rx_buf[3] = app_flexcan_rx_mb.BYTE3;
    rx_buf[4] = app_flexcan_rx_mb.BYTE4;
    rx_buf[5] = app_flexcan_rx_mb.BYTE5;
    rx_buf[6] = app_flexcan_rx_mb.BYTE6;
    rx_buf[7] = app_flexcan_rx_mb.BYTE7;
}
/* EOF. */
