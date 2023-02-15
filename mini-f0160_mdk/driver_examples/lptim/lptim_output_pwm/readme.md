# lptim_output_pwm

## 实验流程

- 初始化 BOARD_LPTIM_PORT，将计数器运行模式设置为 LPTIM_WorkMode_Timer 定时器模式，通过设置 ClockSourceFreqHz(HSI: 8MHz)、Prescaler(1) 和 APP_LPTIM_UPDATE_PERIOD(8000 - 1)，设置计数器为循环工作模式，配置输出波形参数，启动计数器。实现周期为 1ms 的 PWM 波输出。Period = (APP_LPTIM_UPDATE_PERIOD + 1) / (ClockSourceFreqHz / Prescaler)。
- 主函数中每当串口接收到字符，加载预先计算好的 12.5% 至 100% (步长 12.5% ) 的占空比对应的比较值，以实现每次键入都可观察到不同的占空比下的波形。

## 实验结果

lptim_output_pwm example.
PWM value: 1000
PWM value: 2000
PWM value: 3000
PWM value: 4000
PWM value: 5000
PWM value: 6000
PWM value: 7000
PWM value: 8000
