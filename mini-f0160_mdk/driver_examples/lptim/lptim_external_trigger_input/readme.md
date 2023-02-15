# lptim_external_trigger_input

在此样例中，使用杜邦线将某个按键与 LPTIM_ETR 引脚相连，模拟输入电平变换，按键按下时为低电平，松开时为高电平，可以模拟上升沿和下降沿输入。

## 实验流程

- 初始化 BOARD_LPTIM_PORT，通过设置 APP_LPTIM_UPDATE_PERIOD(3), 实现计数器计数值为 3 时产生溢出异常，将计数器运行模式设置为 LPTIM_WorkMode_Trigger 触发模式，使能引脚触发输入，设置为下降沿触发，使能触发输入中断和计数器溢出中断，启动计数器。
- 中断服务函数中检测触发输入中断标志位和计数器溢出中断标志位是否置位，是则通过串口输出对应的事件信息。
- 主循环中循环等待串口接受输入字符，并打印当前计数值。

## 实验结果

lptim_external_trigger_input example.
press input key to lead external trigger input event and counter overflow event happen.
trigger input event happens.
trigger input event happens.
trigger input event happens.
counter overflow event happens.