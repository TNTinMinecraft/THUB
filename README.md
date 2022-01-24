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
消息格式：   
```
上线：
THUB.mianban.bedroom.noline.D
 |      |       |      |    |
协议 设备名称 设备位置 上线 消息尾
名称

用户输入：
THUB.mianban.bedroom.qh.1.D
 |      |       |     | | |
协议 设备名称 设备位置 按 状 消息尾
名称                 键 态

传感器：
THUB.tprhmt.bedroom.c.30.D
 |     |       |    |  | |
协议  设备    设备   单 数 消息尾
名称  名称    位置   位 值

申请总线：
THUB.mianban.bedroom.stop.D
 |      |       |     |   |
协议 设备名称 设备位置 暂停 消息尾
名称

HUB申请成功：
THUB.mianban.badroom.ok.D
 |      |       |     | |
协议 设备名称 设备位置 成 消息尾
名称                 功

释放总线：
THUB.mianban.bedroom.fr.D
 |      |       |     | |
协议 设备名称 设备位置 释 消息尾
名称                 放

总线空闲：
THUB.hub.not.D
 |    |   |   |
协议 设备 空闲 消息尾
名称 名称
```
---
消息逻辑：
```
传感器：当总线空闲时输出
if(总线空闲){
  print(date);
}

用户输入：
如果有改变 停止传感器输出
if(数据改变){
  申请暂停总线;
  if(申请成功){
    print(date);
  }
  释放总线;
}
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
    |-- arduino_shugui //使用arduino制作的书柜灯
        |-- shugui //arduino主程序
        |   |-- shugui.ino
        |-- README.txt //串口数据定义
|-- LICENSE
|-- README.md
```
