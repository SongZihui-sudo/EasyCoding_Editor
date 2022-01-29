#ifndef Code_highlighting_h
#define Code_highlighting_h

#include <iostream>
#include <deque>
#include <fstream>
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
	
	int F_BLACK = 0x01;	// 000001
	int F_RED = 0x02	;	// 000010
	int F_GREEN = 0x03;	// 000011
	int F_YELLOW = 0x04;	// 000100
	int F_BLUE = 0x05	;	// 000101
	int F_DPURPLE = 0x06;	// 000110
	int F_WHITE = 0x07;	// 000111

	int B_BLACK = 0x08;	// 001000
	int B_RED = 0x10	;	// 010000
	int B_GREEN = 0x18;	// 011000
	int B_BROWN = 0x80;	// 100000
	int B_BLUE = 0x88	;	// 101000
	int B_WHITE = 0x90;	// 110000

	//缺一个111000，但就这些了

	int setColor(int color); // color是一个前景色于一个后景色的位或结果
	void resetFColor(); // 重置前景色
	void resetBColor(); // 重置背景色

        //设置字体颜色
        void Set_color(int color);
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
