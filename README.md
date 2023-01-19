# THUB
未完工!  
Unfinished!  
千万不要使用PCB文件打板！（PCB有bug
Never use PCB files to make boards! (PCB are errors
---
This is a THUB project with Arduino as its core. And completely open source, you can copy it at home!  
这是一个THUB项目，核心使用ARDUINO。并且完全开源，你可以在家复刻他!
---
作者主页:[TNTInMinecraft](http://www.tntinminecraft.tech/)  
Author URI:[TNTInMinecraft](http://www.tntinminecraft.tech/)
---
从V0.2后，由曾经的使用串口协议传输数据改为使用MQTT协议传输数据，从此不用解决“忙线的问题”  
---
消息格式：   
```
上线：
THUB.mianban.bedroom.FF:FF:FF:FF:FF:FF.noline
 |      |       |            |           |
协议 设备名称 设备位置      MAC地址       上线
名称

设备输入：
THUB.mianban.bedroom.FF:FF:FF:FF:FF:FF.qh.1
 |      |       |            |         | |
协议 设备名称 设备位置      MAC地址      按 状
名称                                   键 态

传感器：
THUB.tprhmt.bedroom.FF:FF:FF:FF:FF:FF.c.30
 |     |       |            |         |  |
协议  设备    设备        MAC地址      单 数
名称  名称    位置                     位 值

复杂数据传输：
THUB.bookcase.bedroom.FF:FF:FF:FF:FF:FF.1,0,1,1,1,1,1,0,1,1,0,1,0,1,1,1
 |      |        |            |                       |
协议   设备     设备        MAC地址                   数据
名称   名称     位置

```
---
文件夹说明：  
```
|-- THUB
    |-- arduino_mianban //使用arduino制作的控制面板
        |-- 3D_model //3D模型文件
        |   |-- A.stl
        |   |-- B.stl
        |   |-- C.stl
        |   |-- D.stl
        |   |-- 控制面板.123dx //主模型
        |-- mianban //arduino主程序
        |   |-- mianban.ino
        |-- README.txt //串口数据定义
    |-- ESP12-f_bookcase //使用ESP12-f制作的书架灯
        |-- ESP12-f_bookcase //arduino主程序
        |   |-- ESP12-f_bookcase.ino
        |-- README.txt
|-- LICENSE
|-- README.md
```
