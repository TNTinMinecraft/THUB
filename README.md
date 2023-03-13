# THUB
未完工!  
Unfinished!  
千万不要使用PCB文件打板！（PCB有bug  
Never use PCB files to make boards! (PCB are errors  
---
This is a THUB project. And completely open source, you can copy it at home!  
这是一个THUB项目。并且完全开源，你可以在家复刻他!  
---
此项目的提交记录和代码还有格式可能会很奇怪，因为本仓库的作者在编写、提交的同时，也在学习如何使用github  
---
作者主页:[TNTInMinecraft](http://www.tntinminecraft.tech/)  
Author URI:[TNTInMinecraft](http://www.tntinminecraft.tech/)
---
从V0.2后，由曾经的使用串口协议传输数据改为使用MQTT协议传输数据，从此不用解决“忙线的问题”  
从V0.1-next后，使用json传输数据，不再使用"THUB."格式  
---
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
