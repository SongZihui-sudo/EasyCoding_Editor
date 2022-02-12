#include <iostream>
#include "../include/EasyCodingEditor.h"
#include "../include/Code_highlighting.h"
#include "../include/Code_completion.h"
#include <curses.h>
#include <stdio.h>
#include "../include/sql.h"
#include <locale.h>
<<<<<<< HEAD
#include <zlib.h>
#include <boost/timer.hpp>
=======
>>>>>>> 3ccd8e8ce5da919b9527f782736a4cd4c540bab3

using namespace edt;
using namespace std;
using namespace cht;
using namespace cct;

int main(int argc,char* argv[]){
        //设置中文字体
        system("LANG=\"zh_CN.UTF-8\"");        
        setlocale(LC_ALL,"zh_CN.UTF-8");
        /*
____________________  
\_   _____/\_   ___ \ 
 |    __)_ /    \  \/ 
 |        \\     \____
/_______  / \______  /
        \/         \/ 
        */
        //select("../data/user_file.db","COMPANY");
        //select("../data/user_file.db","HIGHLITE_C");
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
        e.commander(argc,argv);
        erase();
        endwin();
        return 0;
}
