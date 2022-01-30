#ifndef Markdown_parser_h
#define Markdown_parser_h

#include <deque>
#include <iostream>
#include <vector>

using namespace std;

namespace mpt{
    class Markdown_parser
    {
    private:
        vector <int> state; 
        deque <deque <string>> convert_arr;
        string key_word[9] = {"#","![","[","---","**","*","```","***",">"};
        char spacial_words[3] = {'#','<','>'};
        int title_num = 0;
        int strong_num = 0;
        int code_num = 0;
    public:
        int Lexical_analysis(deque <deque <string>> ready_convety);
        deque <deque <string>> syntax_conversion(int state,deque <deque <string>> ready_convety);
        Markdown_parser(/* args */) = default;
        ~Markdown_parser() = default;
    };
    
}

#endif