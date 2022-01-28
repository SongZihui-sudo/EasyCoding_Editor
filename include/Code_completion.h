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
        int last_y = 0;
        deque <string> code_completion;
        deque <string> show_code;
    public:        
        string c_str = "";
        //读取文件
        bool read_outfiles(string language);
        //词法分析
        int Lexical_analysis(char c,int pos_y,int pos_x);
        Code_completion() = default;
        ~Code_completion() = default;
    };
}

#endif