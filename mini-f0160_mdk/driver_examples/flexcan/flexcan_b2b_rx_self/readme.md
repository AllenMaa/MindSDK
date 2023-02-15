# flexcan_b2b_rx_self

### 实验过程

+ 初始化 FLEXCAN ，配置传输会使用到的最大Mb数目，配置时钟源和波特率，配置总线唤醒源，配置工作模式为Normal模式，配置自接收，配置时钟和同步设置。
+ 将发送需要用到的MB清空，将接收需要的Mb填入通信ID和接收报文格式。开启发送和接收中断。

+ 根据提示，用户向串口键入任意字符。当串口接收到字符后，flexcan 将准备好的数据报文发送到总线，串口打印输出报文的 id 号和报文数据内容。主程序在发送成功后打印发送成功语句。因为开启了自接收，当接收中断被触发后，串口会同时打印 flexcan 接收到的自己的发送报文。

### 实验现象

flexcan_b2b_self_rx example.
press any key to send frame with id 0x666.
app_flexcan_tx() sending: app_flexcan_tx() done.
app_flexcan_rx() at timestamp 29503 with id 0x666: 0 1 2 3 4 5 6 7

app_flexcan_tx() sending: app_flexcan_tx() done.
app_flexcan_rx() at timestamp 41620 with id 0x666: 0 2 4 6 8 10 12 14

