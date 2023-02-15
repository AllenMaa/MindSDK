# i2c_slave_b2b_basic

## 实验流程

+ i2c_slave_b2b_basic样例配合i2c_master_b2b_basic样例使用。
+ 初始化 i2c 从机，配置自身的从机地址为0x30，使能 i2c。
+ 主程序中循环等待主设备匹配从设备地址，判断当前是否发生数据读写操作，当设备地址匹配后，可进行数据读写。
+ 当从设备 rx fifo 不为空，即主设备进行数据发送，从设备进行数据读取，将接收的数据依次存放于数组中。
+ 当从设备接收到主设备的读请求，从设备进行数据发送。
+ i2c_slave_b2b_basic样例的实验现象需结合i2c_master_b2b_basic样例查看，可通过观察串口打印的i2c_master_b2b_basic样例的数据收发来判断从设备是否正常运行。

## 实验结果

i2c_master_b2b_basic example
press any key to write i2c.
write data: 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
press any key to read i2c.
read data:  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,