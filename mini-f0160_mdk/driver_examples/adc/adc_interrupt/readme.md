# adc_interrupt

## 实验过程

+ 初始化 adc 实例，配置精度12b，ADC输入时钟16分频，运行在常规通道单次转换模式下，右对齐。
+ 使能 adc 转换序列。
+ 使能 adc 实例。
+ 使能 adc 中断。
+ 主函数中，用户根据提示向串口输入任意字符，adc 开始转换比较结果，串口打印结果。

## 实验结果

adc_interrupt example.
press any key to start the conversion.
adc conversion start...
value=4092
adc interrupt done...