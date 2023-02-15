# adc_basic

## 实验过程

+ 初始化 adc 实例，配置精度12b，ADC输入时钟2分频，校准时钟40分频，运行在常规通道单次转换模式下，右对齐。
+ 使能 adc 转换序列。
+ 使能 adc 实例。
+ 主函数中，用户根据提示向串口输入任意字符，adc 开始转换比较结果，串口打印结果。

## 实验结果

adc_basic example.
press any key to start the conversion.
app_adc_run_conv() start...
adc_val= 4092
app_adc_run_conv() done.