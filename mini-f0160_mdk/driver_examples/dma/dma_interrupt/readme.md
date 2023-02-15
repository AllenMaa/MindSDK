# dma_interrupt

## 实验过程

+ 初始化 DMA 实例，内存到外设突发模式，自动重装载值，外设地址自增，内存地址自增，位宽32b，低优先级。
+ 使能 DMA 中断。
+ 对发送区内存进行赋值，并清空接受去内存数据。
+ 用户通过串口发送任意字符，设备返回发送的字符，并开始通过 DMA 进行搬运数据。
+ 数据搬运到一半时触发传输一半完成中断，并打印half。
+ 数据搬运完成后触犯传输完成中断，并打印done.

## 实验结果

dma_burst_interrupt example.
ahalf.
done.
shalf.
done.