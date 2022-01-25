#ifndef Code_highlighting_h
#define Code_highlighting_h

#include <iostream>
#include <deque>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

namespace cht{

    typedef struct pos{
        int x;
        int y;
    }pos;

    class Code_highlighting{
    private:
        deque <string> key_words;
    public:
        //设置字体颜色
        void Set_color(int wr,int wg,int wb,int br,int bg,int bb);
        //rgb初始化
        void rgb_init();
        //词法分析
        bool Lexical_analysis(deque <string> ready_highlight);
        //读取关键词文件
        bool read_setting_files(string language);
        Code_highlighting(/* args */) = default;
        ~Code_highlighting() = default;
    }; 
} // namespace cht

#endif