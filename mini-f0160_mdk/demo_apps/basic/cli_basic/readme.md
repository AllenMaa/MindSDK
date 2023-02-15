# fatfs_wav_player_basic



## 用例说明

本例演示 embedded-cli 的使用，上位机终端软件中输入不同的指令，下位机执行不同的操作。

## 操作过程

+ 在PC机上启动UART串口调试终端（例如Tera Term），连接到开发板。
+ 编译本样例工程，下载可执行程序到开发板。
+ 在UART串口终端看到箭头符号后，输入 hello 指令并回车，终端显示 ”Hello, World“
+ 输入 led on 指令并回车，板载 LED 熄灭。
+ 输入 led off 指令并回车，板载 LED 点亮。

## 运行log

~~~bash
> hello
Hello World.

> led on
> led off
> led on
> led off
~~~



