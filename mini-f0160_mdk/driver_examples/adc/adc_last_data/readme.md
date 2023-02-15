# adc_last_data

## 实验过程

+ 初始化 adc 实例，配置精度12b，ADC输入时钟16分频，运行在常规通道单次转换模式下，右对齐。
+ 使能 adc 转换序列。
+ 使能 adc 实例。
+ 主函数中，用户根据提示向串口输入任意字符，adc 开始转换比较结果，串口打印结果。

## 实验结果

adc_last_data example.
press any key to start the conversion.
app_adc_run_conv() start...
adc_val= 2566
adc_last_val= 0
app_adc_run_conv() done.

app_adc_run_conv() start...
adc_val= 2939
adc_last_val= 2566
app_adc_run_conv() done.

app_adc_run_conv() start...
adc_val= 1902
adc_last_val= 2939
app_adc_run_conv() done.
