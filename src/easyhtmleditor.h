#ifndef _easyhtmleditor_h
#define _easyhtmleditor_h
    #include <iostream>
    #include <vector>

    using namespace std;
    
    string File_Name;
    vector <string> buf;

    class frame{
        private:
            vector <string> parr;
            vector <string> line;
        public:
            frame() = default;
            int shell(vector <string> o_line);
            int write(vector <string> print_to_file,string file_name);
            int input(long long lines);
            int find(string find_Str);
            int read(string read_Str);
    };
    class kennel{
        private: 
            
            string title = "#";
            string img = "![img]";
            string url = "url";
            string split_line = "---";
            string code_begin = "```";
            string code_end = "***";
        public:
            kennel() = default;
            int Title_function(string Tiltle_name);
            int img_function();
            int url_function(string url_things);
            int split_line_function();
            int Gramma_analysis(string Line__);
            int code_begin_funcition();
            int code_end_function();
    };
#endif 