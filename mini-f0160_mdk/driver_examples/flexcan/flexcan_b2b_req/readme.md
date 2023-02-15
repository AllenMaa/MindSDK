# flexcan_b2b_req

### 实验流程

- 初始化 FLEXCAN ，配置传输会使用到的最大Mb数目，配置时钟源和波特率，总线唤醒源，配置工作模式为Normal模式，配置禁止自接收，配置时钟和同步设置。将发送需要用到的MB清空，将接收需要的Mb填入通信ID和接收报文格式。开启中断。
- 当串口接收到任意字符时，会将报文填入相应的 Mb并发送，设置报文类型为远程请求帧。主程序等待全局发送标志位在中断服务程序中被置为 true 后，在主程序打印发送成功语句。
- 主程序等待中断服务程序将全局接收标志设置为true，打印收到的ack报文数据内容。

### 实验现象

flexcan_b2b_req example.
press any key to send remote request frame with id 0x666
app_flexcan_req() sending.
app_flexcan_req() done.
app_flexcan_read() at timestamp 57245 with id 0x666: 1 2 3 4 5 6 7 8

