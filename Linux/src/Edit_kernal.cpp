#include "../include/EasyCodingEditor.h"
#include "../include/Code_highlighting.h"
#include "../include/Code_completion.h"
#include "../include/Markdown_parser.h"
#include <termio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include "../include/key_code.h"

using namespace edt;
using namespace std;
using namespace cht;
using namespace cct;
using namespace mpt;

int _get_input(void);

cht::Code_highlighting C3;
cct::Code_completion cc2;
mpt::Markdown_parser mp2;

int easyhtmleditor::Edit_kernal(){
    initscr();
    mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0");
    if (!out_data.empty());
    else{
        page_arr = {{""}};
    }
    string          str;
    int 		  	ch1 = 0;
    char 		  	ch2 ;
    int 		  	num = 0;
    string        	Parr_str;
    int           	i = 0;
    int			    input_num = 0;

    cbreak();                     
    nonl();                       
    noecho();                     
    keypad(stdscr,true);          
    move(1,0);
    while(ch2 = getch()){
        //printf("key asill %d\n", ch2);
            switch (ch2){
                case BACKSPACE :
                    if (cc2.c_str.empty());
                        else{
                            cc2.c_str.pop_back();
                        }
                       if (last_str.empty());
                    else{
                               last_str.pop_back();
                        }
                        if (pos_x){
                            num = pos_x;
                            pos_x--;
                            last_x--;
                            SetPos(pos_x,pos_y -  (page_now-1)*(page_y-2)+1);
                            if (num<page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].size()&&pos_y- (page_now-1)*(page_y-2)<=page_arr[page_now-1].size()){
                                Parr_str =page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].substr(num);
                                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].erase(pos_x);
                                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)] += Parr_str;
                            }
                            else if(num==page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].size()&&pos_y- (page_now-1)*(page_y-2)<=page_arr[page_now-1].size()){
                                Parr_str = page_arr[page_now-1][pos_y-(page_now-1)*(page_y-2)][page_arr[page_now-1][pos_y-(page_now-1)*(page_y-2)].length()-1];
                                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].pop_back();
                            }
                            else;
                               SetPos(0,pos_y -  (page_now-1)*(page_y-2)+1);
                            clrtoeol();
                            SetPos(0,pos_y -  (page_now-1)*(page_y-2)+1);
                            printw("%s",page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].c_str());
                        }
                    else if(pos_x == 0 && pos_y -  (page_now-1)*(page_y-2) == 0){
                            pos_x = 0;
                           last_x = 0;
                            pos_y = (page_now-1)*(page_y-2);
                       }
                    else if(pos_x==0){
                        pos_x = page_arr[page_now-1][pos_y-1 -  (page_now-1)*(page_y-2)].size();//  out_data[pos_y-1].size();
                        page_arr[page_now-1][pos_y-1 -  (page_now-1)*(page_y-2)] += page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)]; //out_data[pos_y];
                        page_arr[page_now-1].erase(page_arr[page_now-1].begin()+pos_y -  (page_now-1)*(page_y-2));
                        if (page_arr[page_now-1].size() < page_y&&exact_buffer.size()!=0){
                            page_arr[page_now-1].push_back(exact_buffer.top());
                            exact_buffer.pop();
                        }
                        last_str = "";
                        erase();
                        mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
                        for (int i = 0; i < page_arr[page_now-1].size(); i++){
                            move(i+1,0);
                            printw("%s",page_arr[page_now-1][i].c_str());
                            refresh();
                        }
                        pos_y--;
                    }
                    else;
                    refresh();
                    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2);
                    SetPos(pos_x,pos_y -  (page_now-1)*(page_y-2)+1);
                    break;
                //回车
                case ENTER:
                    last_str = "";
                    num = int(pos_y) -  (page_now-1)*(page_y-2);
                    if (pos_x>=page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].size()){
                                page_arr[page_now-1].insert(page_arr[page_now-1].begin()+num+1,"");
                           }
                        else{
                            str = page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].substr(pos_x);
                            page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].erase(pos_x);
                            page_arr[page_now-1].insert(page_arr[page_now-1].begin()+num+1,str);
                        }
                    if (page_arr[page_now-1].size() > page_y){
                            exact_buffer.push(page_arr[page_now-1][page_arr[page_now-1].size()-1]);
                            page_arr[page_now-1].pop_back();
                    }
                    erase();
                    mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
            //SetPos(0,0);
                    for (int i = 0; i < page_arr[page_now-1].size(); i++){
                        move(i+1,0);
                        printw("%s",page_arr[page_now-1][i].c_str());
                        refresh();
                    }
                    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2);
                    pos_x = 0;
                    last_x = 0;
                    pos_y++;
                    if (pos_y>=page_y*(page_now)){
                        pos_y--;
                    }
                    else{
                        SetPos(pos_x,pos_y-(page_now-1)*(page_y-2)+1);
                    }
                    refresh();
                    break;
                    //TAB
                case TAB:
                    if (cc2.c_str.empty());
                    else{
                        cc2.c_str.clear();
                        cc2.c_str = "";
                        last_x = 0;
                        last_str.push_back(' ');
                        last_str.push_back(' ');
                        last_str.push_back(' ');
                        last_str.push_back(' ');
                        last_str.push_back(' ');
                        last_str.push_back(' ');
                        last_str.push_back(' ');
                        last_str.push_back(' ');
                       }
                    if (pos_x){                    
                        num = pos_x;                    
                    }
                    else{
                        num = 0;
                    }
                    pos_x +=8;
                    page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num+1,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num+2,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num+3,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num,' ');
                       page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num+1,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num+2,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num+3,' ');
                    SetPos(0,pos_y -  (page_now-1)*(page_y-2)+1);
                    clrtoeol();
                    SetPos(0,pos_y -  (page_now-1)*(page_y-2)+1);
                    //cout<<page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)];
                    printw("%s",page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].c_str());
                    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2);                                
                    SetPos(pos_x,pos_y -  (page_now-1)*(page_y-2)+1);
                    refresh();                    
                    break;
                //空格
                case SPACE:
                    if (cc2.c_str.empty());
                    else{
                           cc2.c_str.clear();
                        cc2.c_str = "";
                        last_x = 0;
                        last_str.push_back(' ');
                    }
                    if (pos_x){                    
                        num = pos_x;                    
                    }
                    else{
                        num = 0;
                    }
                    pos_x++;
                    page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num,' ');    
                    SetPos(0,pos_y -  (page_now-1)*(page_y-2)+1);
                    clrtoeol();
                    SetPos(0,pos_y -  (page_now-1)*(page_y-2)+1);
                    printw("%s",page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].c_str());
                    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2);                                
                    SetPos(pos_x,pos_y -  (page_now-1)*(page_y-2)+1);
                    refresh();
                    break;
                case PAGE_UP:
                    if (page_now==1){
                        page_now = page_now;
                    }
                    else{
                        page_now--;
                        pos_y= pos_y - (page_y-2);
                    }
                    erase();	
                    move(1,0);
                    mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");                    
                    for (int i = 0; i < page_arr[page_now-1].size(); i++){
                        mvprintw(i+1,0,"%s",page_arr[page_now-1][i].c_str());
                    }					
                    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2);
                    mvprintw(page_y-1,page_x-10,"Page:%d",page_now);
                    SetPos(0,1);
                    if (exact_buffer.size()){
                        for (int i = 0; i < exact_buffer.size(); i++){
                            exact_buffer.pop();
                        }
                    }
                    else;
                    pos_x = 0;
                    break;
                case PAGE_DOWN:
                    if (page_now<=page&&page);
                    else{
                        page++;
                        page_arr.push_back({""});
                        pos_x = 0;
                    }
                    page_now++;
                    pos_y+=(page_y-2);
                    erase();
                    mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
                    //mvprintw(1,0,"%d",page_arr[page_now-1].size());                        
                    for (int i = 0; i < page_arr[page_now-1].size(); i++){
                        mvprintw(i+1,0,"%s",page_arr[page_now-1][i].c_str());
                    }					
                    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2);
                    mvprintw(page_y-1,page_x-10,"Page:%d",page_now);
                    move(1,0);
                    if (exact_buffer.size()){
                        for (int i = 0; i < exact_buffer.size(); i++){
                            exact_buffer.pop();
                        }   
                    }
                    pos_x = 0;
                    refresh();
                    break;
                //上
                case UP:
                    if (pos_y <= (page_now-1)*(page_y-2)){
                        pos_y = pos_y;
                        break;
                    }
                    else{
                        if (pos_y){
                            pos_y--;
                        }
                        else;
                    }
                    mvprintw(page_y-1,page_x-20,"Lines:%d",pos_y);
                    pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)].size();
                    last_x = page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)].size();
                    move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
                    refresh();
                    break;   
                        //下
                case DOWN:
                    if (pos_y-  (page_now-1)*(page_y-2)>=page_arr[page_now-1].size()-1);
                        else pos_y++;
                        mvprintw(page_y-1,page_x-20,"Lines:%d",pos_y);
                        pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)].size();
                        move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
                        refresh();
                        break;
                        //左
                case LEFT:
                    if (pos_x){
                        pos_x--;
                        last_x--;
                    }
                    else;           
                        mvprintw(page_y-1,page_x-30,"%dth",pos_x);                        
                        move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
                        refresh();
                        break;
                        //右
                case RIGHT:
                        if (pos_x>=page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)].size()) pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)].size()+1;
                        else{
                            pos_x++;
                            last_x++;                    
                        }
                        mvprintw(page_y-1,page_x-30,"%dth",pos_x);
                        move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
                        refresh();
                        break;     
                    case ESC:
                        erase();
                        nl();
                        echo();
                        nocbreak();
                        return true;
                    default:     
                        input_num++;
                        int bit_c = 0;
                        string input_str;
                        int mid = 0;
                        int left = word[0];
                        int right = word[word.size()-1];     
                        if (ch2 < left){
                            break;
                        }						                       
                        for (int i = 0; i < word.size(); i++){
                            if (left==0&&right==0){
                                break;
                            }
                            mid = (left+right)/2;
                            if (ch2>mid){
                                left = mid + 1;                            
                            }
                            else if(ch2<mid){
                                right = mid -1;
                            }
                            else{
                                bit_c =1;   
                                printw("%c",ch2);                            
                                refresh();
                                pos_x++;
                                last_x++;
                                break;
                            }
                        }
                        if (bit_c){
                            if (pos_x==1&&pos_y-  (page_now-1)*(page_y-2)>page_arr[page_now-1].size()){
                                input_str.push_back(ch2);
                                page_arr[page_now-1] .push_back(input_str);
                                input_str.clear();
                            }
                            else if(pos_x==1&&pos_y -  (page_now-1)*(page_y-2)<=page_arr[page_now-1].size()){
                                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin(),ch2);
                                move(pos_y -  (page_now-1)*(page_y-2)+1,0);
                                printw("%s",page_arr[page_now-1][pos_y - (page_y-2)*(page_now-1)].c_str());
                            }                 
                            else if(pos_y-  (page_now-1)*(page_y-2)<=page_arr[page_now-1].size()&&pos_x<=page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].size()){
                                num = int(pos_x);
                                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num-1,ch2);
                                move(pos_y -  (page_now-1)*(page_y-2)+1,0);
                                clrtoeol();
                                move(pos_y -  (page_now-1)*(page_y-2)+1,0);
                                printw("%s",page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)].c_str());
                                refresh();
                            }
                            else if(pos_x > page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].size()&&pos_y -  (page_now-1)*(page_y-2)<=page_arr[page_now-1].size()){
                                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].push_back(ch2);
                            }
                            else;  
                            string code_compl = cc2.Lexical_analysis(ch2,pos_y -  (page_now-1)*(page_y-2),last_x,ret_fileread1,page_y,page_x);
                            if (last_x-1  <= cc2.c_str.size()){   
                                if (code_compl[code_compl.length()-1]!=ch2){
                                    SetPos(0,pos_y - (page_now-1)*(page_y-2)+1);   
                                    clrtoeol();                                
                                    page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)].clear();
                                    last_str+=code_compl;                            
                                    page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)] = last_str ;
                                    SetPos(0 ,pos_y - (page_now-1)*(page_y-2)+1);    
                                    //cout<<page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)];
                                    printw("%s",page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)].c_str());
                                    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2); 
                                    pos_x = page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)].size(); 
                                    mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
                                    SetPos(pos_x,pos_y -  (page_now-1)*(page_y-2)+1);     
                                    refresh();                         
                                    break;
                                }
                                else;
                            }       
                            else;                                          
                        }							
                        C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2);
                        mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");                            
                        move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);	
                        refresh();
                        break;
                    }
                    sleep(0.5);
        }	
    return 0;
}
