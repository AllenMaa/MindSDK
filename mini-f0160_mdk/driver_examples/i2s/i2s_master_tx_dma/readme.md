# i2s_master_tx_interrupt

## 实验流程
+ 初始化 i2s 主机模式，设置时钟频率、采样频率、数据宽度、通信协议、主时钟、时钟极性和传输模式等等，使能 i2s 。
+ 使能中断，i2s 传输左右声道数据，清除中断。

## 实验结果

+ play left channel and right channel data