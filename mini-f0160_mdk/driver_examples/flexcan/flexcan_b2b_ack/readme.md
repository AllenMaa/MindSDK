# flexcan_b2b_ack

### 实验流程

- 初始化 FLEXCAN ，配置传输会使用到的最大Mb数目，配置时钟源和波特率，总线唤醒源，配置工作模式为Normal模式，配置不自接收，配置时钟和同步设置。将发送需要用到的MB清空，将接收需要的Mb填入通信ID和接收报文格式。开启中断。缺省情况下，接收匹配时不检查报文的类型和格式。
- 主程序不断检查全局接收标志位。在中断服务程序中检查到对应接收Mb中断发生后，全局发送接收位被置为 true。主程序打印接收到远程请求帧的提示语句。
- 主程序准备好ack数据填入对应的发送Mb，打印数据内容。主程序等待全局发送标志位在发送成功后被中断服务程序设置为true后，打印发送成功提示语句。

### 实验现象

flexcan_b2b_ack example.
waiting for any frames with id 0x666.
app_flexcan_req() at timestamp 48760 with id 0x666.
app_flexcan_ack() sending: 1 2 3 4 5 6 7 8
app_flexcan_ack() done.