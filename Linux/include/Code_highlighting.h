#ifndef Code_highlighting_h
#define Code_highlighting_h

#include <iostream>
#include <deque>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace cht{

    #define RB					1
  	#define BLB					2
    #define GB          3
  	#define YB					4
  	#define BAB					5
  	#define MB					6
  	#define CB					7
    #define WB          8

    //坐标
    typedef struct pos{
        int         x;
        int         y;
    }pos;
    //代码高亮类
    class Code_highlighting{
    private:    
        deque <string> key_words2;
    public:        
        //设置字体颜色
        void Set_color(int color);
        //词法分析
        bool Lexical_analysis(deque <string> ready_highlight,deque <string >file_data,int pos_y);
        void ReSetColor(); 
        Code_highlighting(/* args */){
        };
        ~Code_highlighting() = default;
    }; 
} // namespace cht

#endif