# adc_fixed_seq

## 实验过程

+ 初始化 dma 。
+ 初始化 adc 实例，配置精度12b，ADC输入时钟16分频，运行在 conversion by sequence 模式下，右对齐。
+ 使能 adc 转换序列。
+ 使能 adc 实例。
+ 使能 dma 中断。
+ 主函数中，用户根据提示向串口输入任意字符，adc 开始转换比较结果，串口打印结果。

## 实验结果

adc_fixed_seq example.
press any key to start the conversion.
fixed_seq conversion start...
adc_val[0]= 3110
adc_val[1]= 212
fixed_seq conversion done...