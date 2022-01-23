#ifndef _easyhtmleditor_h
#define _easyhtmleditor_h

#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <Windows.h>

using namespace std;

namespace edt{

class easyhtmleditor{  
private:
    short int pos_x = 0;
    short int pos_y = 0;
    deque <string> out_data;
    deque <string> parr3;
    string key[6] = {"q","i","a","/","wq","v"};
public:
    //打开文件
    bool open_files(string filename);
    //保存文件
    bool save_files(string filename,deque <string> save_Data);
    //新建文件
    bool creat_files();
    //设置光标位置
    static void SetPos(short int x,short int y);
    //查找
    bool find(string finding);
    //控制台
    int commander();
    easyhtmleditor() = default;
    ~easyhtmleditor() = default;
}; 
} // namespace edt

#endif 