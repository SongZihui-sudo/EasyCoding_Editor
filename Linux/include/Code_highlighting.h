#ifndef Code_highlighting_h
#define Code_highlighting_h

#include <iostream>
#include <deque>
#include <fstream>
#include <string>

using namespace std;

namespace cht{
    //前景
    const int F_BLACK = 0x01;	// 000001
    const int F_RED = 0x02;		// 000010
    const int F_GREEN = 0x03;	// 000011
    const int F_YELLOW = 0x04;	// 000100
    const int F_BLUE = 0x05;	// 000101
    const int F_DPURPLE = 0x06;	// 000110
    const int F_WHITE = 0x07;	// 000111
    //背景
    const int B_BLACK = 0x08;	// 001000
    const int B_RED = 0x10;		// 010000
    const int B_GREEN = 0x18;	// 011000
    const int B_BROWN = 0x80;	// 100000
    const int B_BLUE = 0x88;	// 101000
    const int B_WHITE = 0x90;	// 110000
    //坐标
    typedef struct pos{
        int x;
        int y;
    }pos;
    //代码高亮类
    class Code_highlighting{
    private:
        deque <string> key_words;
    public:
        //设置字体颜色
        bool Set_color(int color);
        //词法分析
        bool Lexical_analysis(deque <string> ready_highlight);
        //读取关键词文件
        bool read_setting_files(string language); 
        // 重置前景色
        void resetFColor(); 
        // 重置背景色
        void resetBColor(); 
        Code_highlighting(/* args */) = default;
        ~Code_highlighting() = default;
    }; 
} // namespace cht

#endif