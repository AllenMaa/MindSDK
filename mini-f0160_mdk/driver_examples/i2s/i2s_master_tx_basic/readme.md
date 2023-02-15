# i2s_master_tx_basic

## 实验流程

+ 初始化 i2s 主机模式，设置时钟频率、采样频率、数据宽度、通信协议、主时钟、时钟极性和传输模式等等，使能 i2s 。
+ 主程序中循环等待发送缓冲区非空。
+ 当发送缓冲区非空，i2s 发送左声道数据。
+ 循环等待发送缓冲区非空，i2s 发送右声道数据。

## 实验结果

+ play left channel and right channel data