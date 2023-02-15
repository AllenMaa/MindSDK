# flexcan_b2b_tx

### 实验过程

+ 初始化 FLEXCAN ，配置传输会使用到的最大Mb数目，配置时钟源和波特率，配置总线唤醒源，配置工作模式为Normal模式，配置不自接收，配置时钟和同步设置。
+ 将发送需要用到的MB清空，将接收需要的Mb填入通信ID和接收报文格式。开启发送中断。

+ 用户根据提示，向串口键入任意字符。当串口接收到任意字符时，flexcan 发送 id 号为 APP_FLEXCAN_XFER_ID 的报文上总线，将报文数据通过串口打印输出。发送成功后，flexcan中断被触发，串口打印触发完成的语句。

### 实验现象

flexcan_b2b_tx example.
press any key to send frame with id 0x666
app_flexcan_tx() sending: 0 1 2 3 4 5 6 7
app_flexcan_tx() done.

app_flexcan_tx() sending: 0 2 4 6 8 10 12 14
app_flexcan_tx() done.