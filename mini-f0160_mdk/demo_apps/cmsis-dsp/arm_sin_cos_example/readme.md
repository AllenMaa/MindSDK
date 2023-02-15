# hello_world

## 实验过程

+ 板子初始化。
+ 打印“cos & sin basic examples”。
+ 计算数据buffer的cos(x) & sin(x)，参考和测试的误差，并打印。
+ 用户通过串口向设备发送任意字符，设备通过串口返回用户发送的字符。

## 实验结果

### 用户定义的待计算的x数组

testInput_f32[MAX_BLOCKSIZE] =
{
   1.570796326794896619,  -1.244916875853235400,  -4.793533929171324800,   0.360705030233248850,   0.827929644170887320,  -3.299532218312426900,   3.427441903227623800,   3.422401784294607700,  
   0.941943896490312180,   0.502609575000365850,  -0.537345278736373500,   2.088817392965764500,  -1.693168684143455700,   6.283185307179590700,  -0.392545884746175080,   0.327893095115825040,
   3.070147440456292300,   0.170611405884662230,  -0.275275082396073010,  -2.395492805446796300,   0.847311163536506600,  -3.845517018083148800,   2.055818378415868300,   4.672594161978930800,
  -1.990923030266425800,   2.469305197656249500,   3.609002606064021000,  -4.586736582331667500,  -4.147080139136136300,   1.643756718868359500,  -1.150866392366494800,  -0.108308165334010680
};

### 串口结果打印

cos & sin basic examples.
cosOutput = 0.000000
sinOutput = 1.000000
diff = 0.000000
cosOutput = 0.320136
sinOutput = -0.947352
diff = 0.000037
cosOutput = 0.081054
sinOutput = 0.996692
diff = 0.000036
cosOutput = 0.935631
sinOutput = 0.352928
diff = 0.000036
cosOutput = 0.676389
sinOutput = 0.736519
diff = 0.000037
cosOutput = -0.987545
sinOutput = 0.157282
diff = 0.000017
cosOutput = -0.959408
sinOutput = -0.281968
diff = 0.000031
cosOutput = -0.960824
sinOutput = -0.277131
diff = 0.000016
cosOutput = 0.588209
sinOutput = 0.808692
diff = 0.000028
cosOutput = 0.876326
sinOutput = 0.481712
diff = 0.000006
cosOutput = 0.859060
sinOutput = -0.511851
diff = 0.000025
cosOutput = -0.495156
sinOutput = 0.868790
diff = 0.000025
cosOutput = -0.122067
sinOutput = -0.992520
diff = 0.000004
cosOutput = 1.000000
sinOutput = 0.000000
diff = 0.000000
cosOutput = 0.923937
sinOutput = -0.382542
diff = 0.000002
cosOutput = 0.946709
sinOutput = 0.322044
diff = 0.000030
cosOutput = -0.997438
sinOutput = 0.071384
diff = 0.000022
cosOutput = 0.985475
sinOutput = 0.169784
diff = 0.000013
cosOutput = 0.962333
sinOutput = -0.271807
diff = 0.000037
cosOutput = -0.734333
sinOutput = -0.678772
diff = 0.000024
cosOutput = 0.661999
sinOutput = 0.749501
diff = 0.000006
cosOutput = -0.762295
sinOutput = 0.647203
diff = 0.000035
cosOutput = -0.466219
sinOutput = 0.884648
diff = 0.000038
cosOutput = -0.039784
sinOutput = -0.999194
diff = 0.000028
cosOutput = -0.407870
sinOutput = -0.913025
diff = 0.000027
cosOutput = -0.782389
sinOutput = 0.622769
diff = 0.000026
cosOutput = -0.892733
sinOutput = -0.450573
diff = 0.000012
cosOutput = -0.125320
sinOutput = 0.992103
diff = 0.000027
cosOutput = -0.535675
sinOutput = 0.844419
diff = 0.000009
cosOutput = -0.072895
sinOutput = 0.997336
diff = 0.000008
cosOutput = 0.407691
sinOutput = -0.913106
diff = 0.000026
cosOutput = 0.994130
sinOutput = -0.108095
diff = 0.000022
SUCCESS