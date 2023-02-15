# spi_master_b2b_polling

本实验为b2b实验，一块开发板下载此样例，另一块下载spi_slave_interrupt样例。
主机模式下，spi的nss引脚、mosi引脚和sck引脚配置为复用输出，spi的miso引脚配置为浮空输入。

## 实验流程

+ 配置 SPI 主机模式。
+ 主循环等待键入。将 APP_SPI_BUFF_LEN 长度的 app_spi_tx_buf 数组顺序发出，同时接收来自从机返回的数据，存储在app_spi_rx_buf中，最后进行打印app_spi_rx_buf。
+ 更新 app_spi_tx_buf 中数组值，等待下一次键入。
+ 因为主机发送和接收同时进行，从机只会发送前一刻的数值，所以同一元素在app_spi_rx_buf会比在app_spi_tx_buf的位置向右偏差1。

## 实验结果

spi_master_b2b_polling example.

spi send data:0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
spi received data:0 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14

spi send data:0 2 4 6 8 10 12 14 0 2 4 6 8 10 12 14
spi received data:15 0 2 4 6 8 10 12 14 0 2 4 6 8 10 12