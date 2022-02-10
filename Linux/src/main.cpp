#include <iostream>
#include "../include/EasyCodingEditor.h"
#include "../include/Code_highlighting.h"
#include "../include/Code_completion.h"
#include <curses.h>
#include <stdio.h>
#include "../include/sql.h"
<<<<<<< HEAD
#include <locale.h>
//你好
=======

>>>>>>> b24a99005622586b615081b668379f6a380e5bbc
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
