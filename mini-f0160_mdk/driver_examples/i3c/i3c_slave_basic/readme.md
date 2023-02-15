# i3c_slave_basic

## 实验流程

+ 准备两块开发板，板 A 下载 I2C 样例中的 i2c_master_b2b_basic 样例，板 B 下载本样例，并通过 I2C 接口连接两块开发板。
+ 板 B 初始化 I3C 从机模式，设置时钟频率和 I2C 模式下的静态地址，使能 I3C。
+ 主程序中循环以下任务：
  + 等待设备地址被主机唤起。
  + 等待主机产生停止信号并执行以下任务：
    + 如果 Rx FIFO 非空，读取数据到buffer中
    + 如果 Tx FIFO 非满，且buffer中有数据，将buffer中的数据放入到 Tx FIFO 中等待发送。

## 实验结果

~~~shell
i3c_slave_basic.
xfer done.
xfer done.
xfer done.
xfer done.
~~~

