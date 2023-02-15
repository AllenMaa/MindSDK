# i2c_slave_b2b_interrupt

## 实验流程

+ i2c_slave_b2b_interrupt样例配合i2c_master_b2b_basic样例使用。
+ 初始化 i2c 从机，配置自身的从机地址为0x30，使能 i2c，中断使能。
+ 主程序中循环等待主设备匹配从设备地址，当设备地址匹配后，产生对应中断，可进行数据读写。
+ 当从设备 rx fifo 不为空，即主设备进行数据发送，从设备进行数据读取，将接收的数据依次存放于数组中。
+ 当从设备接收到主设备的读请求，从设备进行数据发送。
+ 从设备样例中按下任意按键可查看当前i2c从机buf中的数值，从而确认是否发生数据传输。

## 实验结果

i2c_slave_interrupt example
i2c slave xfer data: 1 2 3 4 5 6 7 8 0 0 0 0 0 0 0 0
i2c slave xfer data: 1 2 3 4 5 6 7 8 2 3 4 5 6 7 8 9