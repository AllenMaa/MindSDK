# flash_iap

## 实验流程

+ 初始化串口，配置时钟频率、波特率、字长、传输模式等信息。
+ 初始化片内 FLASH。
+ 读取片内 FLASH 指定 PAGE 数据。
+ 擦除片内 FLASH 指定 PAGE 数据。
+ 读取擦除后的片内 FLASH 指定 PAGE 数据。
+ 写入数据到片内 FLASH 指定位置。
+ 循环中，将指定位置的数据通过 UART 输出。

## 实验结果

flash_iap example.

 read page ...

ff ff ff ff ff ff ...

  erase page ...

flash_erase_page() done.

 read page ...

ff ff ff ff ff ff ...

 program page ...

flash_program_page() done.

 read page ...

0  1  2  3  4  5 ...

 done.

press any key to retry the operations ...