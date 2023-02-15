# lptim_basic

## 实验流程

- 初始化 BOARD_LPTIM_PORT，将计数器运行模式设置为 LPTIM_WorkMode_Timer 定时器模式，通过设置 ClockSourceFreqHz(LSI: 4kHz)、Prescaler(1) 和 APP_LPTIM_UPDATE_PERIOD(4000 - 1)，设置循环计数模式，使能计数器溢出中断，使能计数器，实现周期为 1 s定时器。Period = (APP_LPTIM_UPDATE_PERIOD + 1) / (ClockSourceFreqHz / Prescaler)。
- 中断服务函数检查计数器溢出中断标志位是否置位，是则打印 * ，然后清除改位中断标志位，使能计数器。
- 主函数中不作任何处理，在初始化后进入死循环。每过 1s ，串口将打印一个 * 。

## 实验结果

lptim_basic example.

**
