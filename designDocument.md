# 3DP-A lightweight program for 3D object loading and viewing 设计文档

[]()

## 环境与平台

* 语言：C++11
* 框架：OpenGL4.5、QT5.9
* 编译器：Visual Studio 2017
* 编译系统：Windows10 64bit

## 配置环境

在win10下安装Visual Studio 2017，然后安装qt5.9，编译器选择msvc2017 64-bit。在VS的扩展和更新下安装QT Visual Studio扩展，并且配置QT版本和路径。

接下来就可以使用vs2017的编译环境和QTDesigner的界面设计进行开发了，如果想直接使用QTCreator做编辑器也可以。

详细配置步骤可以参考我的博客[https://www.meteorshub.com/computer-graphics/2017/11/146/]()。

## 系统架构简述

### QT

QT是一个跨平台的图形界面设计工具，最新版本是QT5.10，在windows的C++下，是很常见的一个图形界面工具，相比于MFC，更简洁和通俗易懂，也更容易进行设计，现在已经很少有用MFC做界面的了。

### OpenGL

OpenGL是一个跨平台的图形应用程序编程接口，最新版本好像到了4.6，不过我的GTX1080仅支持到4.5。跟OpenGL处于竞争关系的就是大名鼎鼎的DirectX。DirectX是微软出的，用于windows下的图形和游戏开发，现在大部分PC平台的大型游戏都是使用的DX接口，最新版是win10支持的DirectX12。不过OpenGL有一点好处就是跨平台，Linux、mac、移动端等都支持。

另外也可以用WebGL编写，web端的界面可能要好设计一点，但考虑到这个项目在本地运行的情景还是要远远多于web端运行，所以最后选择了QT+OpenGL。

## 遇到的问题与解决方案

作为电子系转到软院的学生，我之前没有用过OpenGL和QT，因此如何上手就是一件关键的事情。网上的教程因为版本更迭，有的已经年久过时，还有的兼容性不好，还好在youtube找到了几个时效性还不错的视频，在我上手时给了我莫大的帮助。

在处理颜色的时候，工程说明里
