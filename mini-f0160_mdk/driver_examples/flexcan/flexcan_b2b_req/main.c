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
#define APP_FLEXCAN_XFER_ID        0x666u   /* The flexcan xfer Id number. */
#define APP_FLEXCAN_REQ_BUF_LEN    0u       /* The flexcan xfer buffer length. */
#define APP_FLEXCAN_ACK_BUF_LEN    8u       /* The flexcan xfer buffer length. */
#define APP_FLEXCAN_XFER_MaxNum    15u      /* Amount of mb to be used. */
#define APP_FLEXCAN_XFER_PRIORITY  0u       /* Priority of the mb frame. */

/*
 * Variables.
 */
volatile bool app_flexcan_tx_flag = false; /* Flag the message buffer transport state. */
volatile bool app_flexcan_rx_flag = false; /* Flag the message buffer transport state. */

uint8_t app_flexcan_rx_buf[APP_FLEXCAN_ACK_BUF_LEN]; /* The flexcan rx buffer for rx mb frame reception. */
FLEXCAN_Mb_Type app_flexcan_rx_mb; /* For message buffer rx frame storage. */

/*
 * Declerations.
 */
void app_flexcan_init(void); /* Setup flexcan. */
void app_flexcan_req(); /* Transport frame. */
void app_flexcan_read(uint8_t *rx_buf); /* Transport frame. */
/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();
    printf("\r\nflexcan_b2b_req example.\r\n");

    /* Setup the flexcan module.*/
    app_flexcan_init();
    printf("press any key to send remote request frame with id 0x%x\r\n", (unsigned)APP_FLEXCAN_XFER_ID);

    while (1)
    {
        getchar();

        /* Send a message through flexcan. */
        printf("app_flexcan_req() sending.\r\n");
        app_flexcan_req();

        /* Wait for tx done. */
        while (!app_flexcan_tx_flag) /* This flag will be on when the Tx interrupt is asserted. */
        {
        }
        printf("app_flexcan_req() done.\r\n");

        /* Wait for rx done. */
        while (!app_flexcan_rx_flag) /* This flag will be on when the Rx interrupt is asserted. */
        {
        }
        app_flexcan_rx_flag = false;
        printf("app_flexcan_read() at timestamp %u with id 0x%x: ", (unsigned)app_flexcan_rx_mb.TIMESTAMP, (unsigned)app_flexcan_rx_mb.ID);
        for (uint8_t i = 0u; i<APP_FLEXCAN_ACK_BUF_LEN; i++)
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
    flexcan_init.MaxXferNum = APP_FLEXCAN_XFER_MaxNum; /* The max mb number to be used. */
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

    /* Set tx mb. */
    FLEXCAN_ResetMb(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH);
    FLEXCAN_SetMbCode(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH, FLEXCAN_MbCode_TxInactive);

    /* Enable intterupts for tx mb. */
    /* Remote request use the same mb for sending and receiving. */
    FLEXCAN_EnableMbInterrupts(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_INT, true);
    NVIC_EnableIRQ(BOARD_FLEXCAN_IRQn);
}

/* Interrupt request handler. */
void BOARD_FLEXCAN_IRQHandler(void)
{
    /* Judge the xfer event. */
    if (0u!= (FLEXCAN_GetMbStatus(BOARD_FLEXCAN_PORT) & BOARD_FLEXCAN_TX_MB_STATUS) ) /* Remote request use the same mb for sending and receiving. */
    {
        /* Clear flexcan mb interrupt flag. */
        FLEXCAN_ClearMbStatus(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_STATUS);
        if (!app_flexcan_tx_flag)
        {
            /* Update the tx flag. */
            app_flexcan_tx_flag = true;
        }
        else
        {
            /* Read the message. */
            app_flexcan_read(app_flexcan_rx_buf);

            /* Update the tx and rx flag. */
            app_flexcan_rx_flag = true;
            app_flexcan_tx_flag = false;
        }
    }
}

/* Send a message frame. */
void app_flexcan_req()
{
    FLEXCAN_Mb_Type mb;
    mb.ID = APP_FLEXCAN_XFER_ID; /* Indicated ID number. */
    mb.TYPE = FLEXCAN_MbType_Remote; /* Data frame type. */
    mb.FORMAT = FLEXCAN_MbFormat_Standard; /* STD frame format. */
    mb.PRIORITY = APP_FLEXCAN_XFER_PRIORITY; /* The priority of the frame mb. */

    /* Set the workload size. */
    mb.LENGTH = APP_FLEXCAN_REQ_BUF_LEN;

    /* Send. */
    FLEXCAN_WriteTxMb(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH, &mb);
    /* Update the request send flag. */
    FLEXCAN_SetMbCode(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH, FLEXCAN_MbCode_TxDataOrRemote); /* Write code to send. */
}

/* Receive a message frame. */
void app_flexcan_read(uint8_t *rx_buf)
{
    /* Read the info from mb and reconstruct for understanding. */
    FLEXCAN_ReadRxMb(BOARD_FLEXCAN_PORT, BOARD_FLEXCAN_TX_MB_CH, &app_flexcan_rx_mb);
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
