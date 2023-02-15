# spi_slave_b2b_interrupt

本实验为b2b实验，一块开发板下载此样例，另一块下载spi_master样例。

## 实验流程

+ 配置 SPI 从机模式。 使能接收中断。
+ 当从机接收主机传来的数据时，会进入中断处理函数。每次进入，更新app_spi_xfer_cnt，并将接收到的数据填入自己的发送缓冲区，等待下一次发送。
+ 主程序循环等待键入。打印app_spi_xfer_cnt，此值表明从机进入了多少次接收中断。
+ 因为spi_master样例中每次以 APP_SPI_BUFF_LEN 为单位进行发送，所以当主机发送完毕时打印的app_spi_xfer_cnt值始终将为 APP_SPI_BUFF_LEN 的整数倍。

## 实验结果

spi_slave_b2b_interrupt example.

spi slave interrupt count:16.

spi slave interrupt count:32.