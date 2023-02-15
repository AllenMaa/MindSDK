# spi_master_b2b_interrupt

本实验为b2b实验，一块开发板下载此样例，另一块下载spi_slave_interrupt样例。
主机模式下，spi的nss引脚、mosi引脚和sck引脚配置为复用输出，spi的miso引脚配置为浮空输入。

## 实验流程

+ 配置 SPI 主机模式。配置接收中断，重写中断处理函数。
+ 主循环等待键入。键入后，调用spi_xfer，配置handler并且开启传输中断。
+ 完成设定的传输要求后，中断服务程序关闭发送和接收中断，回调callback函数，将全局标志位置为true。
+ 主循环等待全局标志位置为true，打印接收数组，并更新 app_spi_tx_buf 中数组值，等待下一次键入。
+ 因为主机发送和接收同时进行，从机只会发送前一刻的数值，所以同一元素在app_spi_rx_buf会比在app_spi_tx_buf的位置向右偏差1。

## 实验结果

spi_master_b2b_interrupt example.
spi tx data:0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
spi xfer len: 16
spi rx data:15 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14

spi tx data:1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0
spi xfer len: 16
spi rx data:15 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15