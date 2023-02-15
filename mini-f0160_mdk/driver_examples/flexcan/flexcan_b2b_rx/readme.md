# flexcan_b2b_rx

### 实验流程

+ 初始化 FLEXCAN ，配置传输会使用到的最大Mb数目、配置时钟源和波特率、总线唤醒源、Normal工作模式、不自接收、时钟和同步设置。
+ 将发送需要用到的MB清空，将接收需要的Mb填入通信ID和接收报文格式。开启接收中断。

+ 当 flexcan 接收到总线上 id 为 APP_FLEXCAN_XFER_ID 的报文时，flexcan 的中断被触发，串口打印输出报文的时间戳、id 号和报文数据内容。

### 实验现象

flexcan_b2b_rx example.
waiting for frame with id 0x666 ...
app_flexcan_read() at timestamp 3227 with id 0x666: 0 1 2 3 4 5 6 7

app_flexcan_read() at timestamp 50514 with id 0x666: 0 2 4 6 8 10 12 14

