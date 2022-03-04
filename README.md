# 简·编辑器 
## 简介  
这是一个简单的文本编辑器，在操作上类似vim。    

1.支持对C/C++关键词的高亮与补全。（把可高亮与可补全的关键词放入了数据库，可以自定义添加关键字）。  
2.Html标签简化，可导出标准的Html，在服务器上可用此编辑器转换文章（用简化的标签写的）为Html，建立小型博客网站。在该编辑器中已经集成了[EASH-HTML-MAKER](https://github.com/SongZihui-sudo/Easy-HTML-MAKER)   
## 进展
### Web版   
[在线使用](http://s-zh.space/Blog/editor/html/index.html)    
在Web版中已经通过模拟光标，实现了基本的编辑操作。      
采用了pieces table的数据结构，底层使用链表实现。   
实现了C/C++简单的代码高亮   
![img](https://github.com/SongZihui-sudo/EasyCoding_Editor/blob/Windows/%E6%88%AA%E5%9B%BE/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202022-03-01%20234820.jpg)
## 截图

C/C++   
![img](https://github.com/SongZihui-sudo/EasyCoding_Editor/blob/Windows/%E6%88%AA%E5%9B%BE/Screenshot%202022-02-12%20204140.png)  
HTML   
![img](https://github.com/SongZihui-sudo/EasyCoding_Editor/blob/Windows/%E6%88%AA%E5%9B%BE/Screenshot%202022-02-12%20204050.png)   
EASYHTML   
![img](https://github.com/SongZihui-sudo/EasyCoding_Editor/blob/Windows/%E6%88%AA%E5%9B%BE/Screenshot%202022-02-12%20204630.png)

## 开发环境与开发工具
Vscode

Linux 
	Ubuntu 20.04  
	gcc 9.3.0  
	g++ 9.3.0  
Windows 
	Windows10  
	mingw32 gcc8.1.0 g++8.1.0  
   
## 安装 

该程序主要应用于Linux平台，也有Windows版本。
  
### Linux  

解开压缩包
tar –xvf EasyCoding_Editor.tar
或从网络上下载源码 sudo git clone https://github.com/SongZihui-sudo/EasyCoding_Editor
进入Linux文件夹  
1.编译源码  

cd 到 build 文件夹 ，在终端输入make  

2.运行  

cd 到 bin 文件夹  

会有一个文件名为EC的文件。  
终端输入 ./EC -v 会输出EW:简·编辑器 Linux version:1.0 ,编译成功。  

### Windows    

解开压缩包  
或从网络上下载源码  
git clone https://github.com/SongZihui-sudo/EasyCoding_Editor  
1.编译源码  
    进入Windows文件夹  
    进入Build   
    win+r，打开运行，输入cmd。  
    再在cmd中输入mingw32-make  
2.运行   
在该目录下会生成可执行文件，鼠标点击打开。  

## 编辑器中的一些操作
i and a 像vim一样进入编辑模式,创建一个新文件  
wq \n filename 保存文件  
方向键上 向上移动光标  
方向键下 向下移动光标  
方向键左 向左移动光标  
方向键右 向右移动光标  
回车 插入空行  
删除 删除  
空格 插入空格  
q 不保存直接退出  
\ 字符串 在文件中进行查照  
v 文件名 打开一个文件  
page up 上一页    
page down 下一页  
g \n xxxx gcc命令编译C/C++代码  
h \n 文件名 转换导出html  

./EC -v    
./EC 文件名  
./EC -h 文件名  


## Html标签简化
标题标签：#  
图像标签：img 图片的链接  
链接标签：url 网址 名称  
代码块标签：  
三个\` 表示开始  
三个* 表示结束  
中间的内容表示代码  
引用标签 > 
分割线标签 --- 再单独一行  
强调（加粗） __ 两个_  
[会导致崩溃，有问题] 拓展标签 :: 拓展名  

## 关于Web版的主题配置  
json:
```
{
    "bit":"1",
    "backgroundculor": "#000000",
    "sidemenucolor": "#808080",
    "fontcolor":"#FFFFFF",
    "hightcorlor":"#FF9900",
    "hovercolor":"#00FA9A",
    "cursorcolor":"#FFD700"
}
```
```
bit 保存标志位     
backgroundculor 背景颜色   
sidemenucolor 边栏和顶部菜单，边框颜色   
fontcolor 字体颜色   
highcorlor 高亮颜色      
hovercolor 鼠标悬浮颜色      
cursorcolor 光标颜色   
```
