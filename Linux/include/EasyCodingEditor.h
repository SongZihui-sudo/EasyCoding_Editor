#ifndef _easyhtmleditor_h
#define _easyhtmleditor_h

#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <vector>
#include <stack>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<termios.h>
#include <curses.h>
#include "../include/Code_highlighting.h"

using namespace std;

namespace edt{

using namespace cht;

class easyhtmleditor{  

private:
    int         page_now = 1;
    int         page = 0;
    int         overflow_pagey = 0;
private:    
    stack<string>      save_pop;
    deque <string> ret_fileread1;
    deque <string> ret_fileread2;
    deque < deque <string> > page_arr;
    stack <string> up_do_buffer;
    deque <string> parr3;
    string       key[10] = {"q","i","a","/","wq","v","b","g","h","help"};
    string       language[2] = {"c","cpp"};
    deque < deque <string> > exact_buffer;
public:    
    string      last_str = "";    
    deque <string> out_data;
    int         pos_x = 0;
    int         pos_y = 0; 
    int         last_x = 0;
    int         page_x = 0;
    int         page_y = 0;
    int         ZH_CH_BIT = 0;
    //字符集
    vector <int> word = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W',        'X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    '1','2','3','4','5','6','7','8','9','0', ':',',','{','}','=','+','-','_','\\',';','?','/','>','<','.','\'','\"','@','|','!','$','%','^','&','*','(',')','~','`','#'};
public:
    //打开文件
    bool open_files(string filename);
    //保存文件
    bool save_files(string filename,deque < deque <string> > save_Data);
    //设置光标位置
    static void SetPos(int x,int y);
    //查找
    bool find(string finding);
    //控制台
    int commander(int argc,char* argv[]);
    //获取屏幕高度与宽度
    void print_size();    
    //获得键盘事件
    int Edit_kernal();
    // 输出
    void printl(string ready_print,int x,int bit);
    //方向键上
    void up();
    //方向键下
    void down();
    //方向键左
    void left();
    //方向键右
    void right();
    //page up
    void page_up_();
    //page down
    void page_down_();
    //ESC 
    void ESC_();
    //space
    void space();
    //tab
    void tab();
    //enter
    void enter();
    //backspace
    void backspace();
    //default
    int default_(char ch2);
    void CLEAR(){
        erase();
    }
    //显示这一整页
    int printg(deque <string> print_page);
    easyhtmleditor() = default;
    ~easyhtmleditor() = default;
}; 
} // namespace edt

#endif 
