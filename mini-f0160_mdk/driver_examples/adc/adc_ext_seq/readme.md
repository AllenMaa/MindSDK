# adc_ext_seq

## 实验过程

+ 初始化 adc 实例，配置精度12b，ADC输入时钟16分频，运行在conversion external channel sequence模式下，右对齐。
+ 使能 adc 转换序列。
+ 使能 adc 实例。
+ 主函数中，用户根据提示向串口输入任意字符，adc 开始转换比较结果，串口打印结果。

## 实验结果

adc_ext_seq example.
press any key to start the conversion.
any_inject conversion start...
adc_val[0] = 4091
adc_val[1] = 3109
adc_val[2] = 212
adc_val[3] = 3110
seq conversion done.

ext_value=212
ext_seq conversion done.