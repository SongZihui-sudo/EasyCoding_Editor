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

using namespace std;

namespace edt{

class easyhtmleditor{  

private:
    int page_now = 1;
private:
    deque < deque <string> > page_arr;
    deque <string> parr3;
    string key[10] = {"q","i","a","/","wq","v","b","g","h","help"};
    string language[2] = {"c","cpp"};
    stack <string> exact_buffer;
public:    
    string last_str = "";    
    deque <string> out_data;
    int pos_x = 0;
    int pos_y = 0; 
    int last_x = 0;
    int page_x = 0;
    int page_y = 0;
    //字符集
    vector <int> word = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                    '1','2','3','4','5','6','7','8','9','0',
                    ':',',','{','}','=','+','-','_','\\',';','?','/','>','<','.','\'','\"','@','|','!','$','%','^','&','*','(',')','~','`'};
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
    int commander();
    //获取屏幕高度与宽度
    void print_size();    
    //获得键盘事件
    int Edit_kernal();
    //左移光标
    void MOVELEFT(int x){
        printf("\033[%dD", (x));
    };
    //右移光标
    void MOVERIGHT(int x){
        printf("\033[%dC",(x));
    };
    //上移光标
    void MOVEUP(int y){
        printf("\033[%dA", (y));
    };
    //下移光标
    void MOVEDOWN(int y){
        printf("\033[%dB", (y));
    };
    //清屏
    void CLEAR(){
        system("clear");
    }
    //asill
    char _get_input(void);
    //显示这一整页
    int printg(deque <string> print_page);
    //检测键盘输入
    int kbhit(void);
    //初始化
    void initial(){
      	initscr();                                 //开启curses模式
      	cbreak();                               //开启cbreak模式,除了 DELETE 或 CTRL 等仍被视为特殊控制字元外一切输入的字元将立刻被一一读取
      	//nonl();                                   //用来决定当输入资料时, 按下 RETURN 键是否被对应为 NEWLINE 字元
      	//noecho();                             //echo() and noecho(): 此函式用来控制从键盘输入字元时是否将字元显示在终端机上
      	nl();
	echo();
	intrflush(stdscr,false);
      	keypad(stdscr,true);          //当开启 keypad 後, 可以使用键盘上的一些特殊字元, 如上下左右>等方向键
      	refresh();                              //将做清除萤幕的工作
    }
    easyhtmleditor() = default;
    ~easyhtmleditor() = default;
}; 
} // namespace edt

#endif 
