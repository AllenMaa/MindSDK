# lptim_wakeup_sleep

在此样例中，使用杜邦线将某个按键与 LPTIM_ETR 引脚相连，模拟输入电平变换，按键按下时为低电平，松开时为高电平，可以模拟上升沿或下降沿输入。

## 实验流程

- 初始化 BOARD_LPTIM_PORT，将计数器运行模式设置为 LPTIM_WorkMode_WakeUpLowPower 唤醒低功耗模式，通过设置 ClockSourceFreqHz(LSI: 4kHz)、Prescaler(1) 和 APP_LPTIM_UPDATE_PERIOD(4000 - 1)，实现定时器周期为 1 s。配置引脚触发输入，使能计数器溢出中断，使能计数器，进入 Sleep 模式。Period = (APP_LPTIM_UPDATE_PERIOD + 1) / (ClockSourceFreqHz / Prescaler)。
- 中断处理函数检查中断标志位中更新位是否置为1，清除中断标志位，停止计数器。
- 等待外部引脚唤醒 MCU 后，在主函中串口将打印 "Wake up from sleep mode."。

## 实验结果

lptim_wakeup_sleep example.
press trigger input pin to wake up MCU from sleep mode.
Wake up from sleep mode.
