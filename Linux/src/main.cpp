#include <iostream>
#include "../include/EasyCodingEditor.h"
#include "../include/Code_highlighting.h"
#include "../include/Code_completion.h"
#include <curses.h>
#include <stdio.h>
#include "../include/Markdown_parser.h"

using namespace edt;
using namespace std;
using namespace cht;
using namespace cct;
using namespace mpt;

int main(int argc,char** argv){
        /*
\_   _____/  \    /  \
 |    __)_\   \/\/   /
 |        \\        / 
/_______  / \__/\  /  
        \/       \/
        */
        edt::easyhtmleditor e;
        cct::Code_completion c2;
        e.print_size();
        //初始化字符集
        int k = 0;
        for (int i = 0; i < e.word.size()-1; i++){
                for (int j = 0; j < e.word.size()-i-1; j++){
                        if (e.word[j] > e.word[j+1]){
                            k = e.word[j];
                            e.word[j] = e.word[j+1];
                            e.word[j+1] = k;
                        }   
                }
        }
        if (argc>1){
            string file_name = argv[1];
            if(e.open_files(file_name));
            else{
                mvprintw(e.page_y-2,1,"Can not find %s",argv[1]);
                refresh();
            }
            e.Edit_kernal();
        }
        else{
            e.commander();
        }
        erase();
        endwin();
        return 0;
}
