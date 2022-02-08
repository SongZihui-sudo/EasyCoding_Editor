#ifndef Code_completion_h
#define Code_completion_h

#include <deque>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace cct{
    class Code_completion{
    private:
        int         last_y = 0;
        int         bit = 0;
        int         last_x = 0;
        string      last_str = "";
        deque <string> code_completion;
        deque <string> show_code;
    public:        
        string      c_str = "";
        //读取文件
        deque <string> read_outfiles(string language);
        //词法分析
        string Lexical_analysis(char c,int pos_y,int pos_x,deque <string> file_data,int page_y,int page_x);
        Code_completion() = default;
        ~Code_completion() = default;
    };
}

#endif