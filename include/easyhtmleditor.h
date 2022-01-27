#ifndef _easyhtmleditor_h
#define _easyhtmleditor_h

#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <Windows.h>
#include <vector>

using namespace std;

namespace edt{

class easyhtmleditor{  
private:
    deque <string> parr3;
    string key[6] = {"q","i","a","/","wq","v"};
    string language[2] = {"c","cpp"};
public:    
    char ch2 = 0;
    deque <string> out_data;
    short int pos_x = 0;
    short int pos_y = 0; 
    //字符集
    vector <int> word = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                    '1','2','3','4','5','6','7','8','9','0',
                    ':',',','{','}','=','+','-','_','\\',';','?','/','>','<','.','\'','\"','@','|','!','$','%','^','&','*','(',')','~','`'};
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