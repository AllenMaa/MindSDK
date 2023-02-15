# flexcan_loopback

### 实验过程

+ 初始化 FLEXCAN ，配置传输会使用到的最大 Message Buffer (  Mb ) 数目，配置时钟源和波特率，配置总线唤醒源，配置工作模式为LoopBack回环测试，配置自接收，配置时钟和同步设置。
+ 将发送需要用到的MB清空，将接收需要的Mb填入通信ID和接收报文格式。开启接收中断。

+ 用户根据提示，向串口键入任意字符。每当串口接收到字符时，flexcan 发送 id 号为 APP_FLEXCAN_XFER_ID 的报文。发送完后 flexcan 产生接收中断，读出报文值，并打印输出。

### 实验结果

flexcan_loopback example.
press any key to send loop back frame with id 0x666.
app_flexcan_tx() done.
app_flexcan_read(): 0 1 2 3 4 5 6 7

app_flexcan_tx() done.
app_flexcan_read(): 0 2 4 6 8 10 12 14

app_flexcan_tx() done.
app_flexcan_read(): 0 3 6 9 12 15 18 21

