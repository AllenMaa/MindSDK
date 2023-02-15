# i2c_master_b2b_basic

## 实验流程

+ i2c_master_b2b_basic样例配合i2c_slave_b2b_basic样例或i2c_slave_b2b_interrupt样例使用。
+ 初始化 i2c 主机，设置时钟频率和波特率，设置目标设备地址为0x30，该目标地址要与从机样例中配置的地址一致，使能 i2c。
+ 主程序中循环等待串口键入任意字符。
+ 当串口接收到字符后，i2c 写准备的数组，并打印写操作结果。
+ 当串口再一次接收到字符时，i2c 读数，并打印读操作结果。
+ i2c板对板之间的通信不需要发送目标地址寄存器的数据，即收发数据相同，主机发送8个数据，从机就会接收8个数据。

## 实验结果

i2c_master_b2b_basic example
press any key to write i2c.
write data: 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
press any key to read i2c.
read data:  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,