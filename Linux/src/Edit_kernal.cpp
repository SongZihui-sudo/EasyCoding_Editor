#include "../include/EasyCodingEditor.h"
#include "../include/Code_highlighting.h"
#include "../include/Code_completion.h"
#include <stdio.h>
#include "../include/key_code.h"
#include <string.h>

using namespace edt;
using namespace std;
using namespace cht;
using namespace cct;

int _get_input(void);

cht::Code_highlighting C3;
cct::Code_completion cc2;

int easyhtmleditor::Edit_kernal(){
    initscr();
    if (!exact_buffer.empty());
    else{
        exact_buffer = {{""}};
    }
    mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0");
    if (!page_arr.empty());
    else{
        page_arr = {{""}};
    }
    string          str;
    //char 		  	ch1 = '0';
    char 		  	ch2 = '0'; 
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
                //如果退格键失效删下面的注释，注释上面
                case 7:
                case BACKSPACE :backspace();break;
                //回车
                case ENTER:enter();break;
                    //TAB
                case TAB:tab(); break;
                //空格
                case SPACE:space();break;
                case PAGE_UP:page_up_();break;
                case PAGE_DOWN:page_down_();break;
                //上
                case UP:up();break;   
                        //下
                case DOWN:down();break;
                        //左
                case LEFT:left();break;
                        //右
                case RIGHT:right();break;     
                case ESC:ESC_();return true;
                default:     default_(ch2);break;
            }
    }	
    return 0;
}
//效率低下已修改
void easyhtmleditor::printl(string ready_print,int x,int bit){
    char c;
    const char* str = ready_print.c_str();
    int bit_cn = 0;
	while(1){
		c=*str++;
		if (c==0) break; //如果到字符串尾则说明该字符串没有中文字符
		if (c&0x80) //如果字符高位为1且下一字符高位也是1则有中文字符
		if (*str & 0x80) bit_cn = 1;
	}
    if (bit_cn){
        for (int n = 0; n < ready_print.size(); ){
            if (ready_print[n]<=-1&&ready_print[n]>=-128){
                if (bit){
                    mvprintw(x+1,n,"%c%c%c",ready_print[n],ready_print[n+1],ready_print[n+2]);    
                }
                else            
                    mvprintw(pos_y-(page_now-1)*(page_y-2)+1,n,"%c%c%c",ready_print[n],ready_print[n+1],ready_print[n+2])    ;                                                                   
                n+=3;
            }
            else{   
                if (bit){
                    mvprintw(x+1,n,"%c",ready_print[n]);            
                }
                else                                   
                    mvprintw(pos_y-(page_now-1)*(page_y-2)+1,n,"%c",ready_print[n]);
                n++;
            }                                            
        move(pos_y-(page_now-1)*(page_y-2)+1,pos_x+1);                                            
        refresh();
        }
    }
    else{
        move(x+1,0);
        printw("%s",ready_print.c_str());
        refresh();
    }
}

void easyhtmleditor::up(){
    if (pos_y == (page_now-1)*(page_y-2)&&!save_pop.empty()){
        exact_buffer[page_now-1].push_front(page_arr[page_now-1][page_arr[page_now-1].size()-1]);
        page_arr[page_now-1].pop_back();
        page_arr[page_now-1].push_front(save_pop.top());
        save_pop.pop();
        erase();
        for (int i = 0; i < page_arr[page_now-1].size(); i++){
            printl(page_arr[page_now-1][i],i,1);
        }
        C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y);
        mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
    }
    else if (pos_y <= (page_now-1)*(page_y-2)&&overflow_pagey==0){
        pos_y = pos_y;
    }
    else{
        if (pos_y){
            pos_y--;
        }            
    }
    mvprintw(page_y-1,page_x-20,"Lines:%d",pos_y+overflow_pagey);
    pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)].size();
    last_x = page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)].size();
    move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
    refresh();
}

void easyhtmleditor::down(){
    if (pos_y-  (page_now-1)*(page_y-2)>=page_y-2 && exact_buffer[page_now-1][0]!=""){       
        overflow_pagey++;
        if (exact_buffer[page_now-1][0] == ""){
            exact_buffer[page_now-1].pop_front();
        }
        erase();
        save_pop.push(page_arr[page_now-1][0]);
        page_arr[page_now-1].pop_front();
        for (int i = 0;i<page_arr[page_now-1].size() ; i++){
            printl(page_arr[page_now-1][i],i,1);
        }
        page_arr[page_now-1].push_back(exact_buffer[page_now-1][exact_buffer[page_now-1].size()-1]);
        printl(exact_buffer[page_now-1][exact_buffer[page_now-1].size()-overflow_pagey],0,0);        
        exact_buffer[page_now-1].pop_back();
        C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y);
        mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
    }
    else if (pos_y-  (page_now-1)*(page_y-2)==page_arr[page_now-1].size()-1){
        //pos_y++;
        pos_y = pos_y;
    }
    else{
        pos_y++;
    } 
    mvprintw(page_y-1,page_x-20,"Lines:%d",pos_y+overflow_pagey);
    pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)].size();
    move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
    refresh();
}

void easyhtmleditor::left(){
    if (pos_x<=0){
        pos_x = 0;
        mvprintw(page_y-1,page_x-30,"%dth",pos_x);                        
        move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
        refresh();
    }
    else if(page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)][pos_x-1]<=-1&&page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)][pos_x-1] >=-128&&pos_x>0){
        pos_x = pos_x-3;
        mvprintw(page_y-1,page_x-30,"%dth",pos_x);                        
        move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
        refresh();
    }
    else{
        pos_x--;
        last_x--; 
        mvprintw(page_y-1,page_x-30,"%dth",pos_x);                        
        move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
        refresh();
    }
}

void easyhtmleditor::right(){
    if (pos_x>=page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)].size()) 
        pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)].size();     
    else if(page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)][pos_x+1]<=-1&&page_arr[page_now-1][pos_y-  (page_now-1)*(page_y-2)][pos_x+1]>=-128){
        pos_x = pos_x+3;
        mvprintw(page_y-1,page_x-30,"%dth",pos_x);                        
        move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
        refresh();
    }
    else{
        pos_x++;
        last_x++;  
        mvprintw(page_y-1,page_x-30,"%dth",pos_x);
        move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
        refresh();                  
    }                    
}

void easyhtmleditor::ESC_(){
    erase();
    nl();
    echo();
    nocbreak();
}

void  easyhtmleditor::space(){
    int num = 0;
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
    printl(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)],0,0);
    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y);                                
    SetPos(pos_x,pos_y -  (page_now-1)*(page_y-2)+1);
    refresh();
}

void easyhtmleditor::tab(){
    int num = 0;
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
    printl(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)],0,0);
    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y);                                
    SetPos(pos_x,pos_y -  (page_now-1)*(page_y-2)+1);
    refresh();   
}

void easyhtmleditor::enter(){
    int num = 0;
    last_str = "";
    num = int(pos_y) -  (page_now-1)*(page_y-2);
    if (pos_x>=page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].size()){
        page_arr[page_now-1].insert(page_arr[page_now-1].begin()+num+1,"");
    }
    else{
        string str = page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].substr(pos_x);
        page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].erase(pos_x);
        page_arr[page_now-1].insert(page_arr[page_now-1].begin()+num+1,str);
    }
    if (page_arr[page_now-1].size() > page_y-1){
        exact_buffer[page_now-1].push_front(page_arr[page_now-1][page_arr[page_now-1].size()-1]);
        page_arr[page_now-1].pop_back();
    }
    erase();
    mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
    move(0,0);
    for (int i = 0; i < page_arr[page_now-1].size(); i++){
        move(i+1,0);
        printl(page_arr[page_now-1][i],i,1);
    }
    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y);
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
}

void easyhtmleditor::page_up_(){
    overflow_pagey = 0;
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
        printl(page_arr[page_now-1][i],i,1);
    }
    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y);
    mvprintw(page_y-1,page_x-10,"Page:%d",page_now);
    SetPos(0,1);
    pos_x = 0;
}

void easyhtmleditor::page_down_(){
    overflow_pagey = 0;
    exact_buffer.push_back({""});
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
    for (int i = 0; i < page_arr[page_now-1].size(); i++){
        printl(page_arr[page_now-1][i],i,1);
    }			
    C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y);
    mvprintw(page_y-1,page_x-10,"Page:%d",page_now);
    move(1,0);
    pos_x = 0;
    refresh();
}

void easyhtmleditor::backspace(){
    if (cc2.c_str.empty());
    else{
        cc2.c_str.pop_back();
    }
    if (last_str.empty());
    else{
        last_str.pop_back();
    }
    if (pos_x){
        int num = pos_x;
        pos_x--;
        last_x--;
        string Parr_str;
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
        printl(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)],0,0);
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
        if (page_arr[page_now-1].size() < page_y&&exact_buffer[page_now-1].size()!=0){
            page_arr[page_now-1].push_back(exact_buffer[page_now-1][exact_buffer[page_now-1].size()]);
            exact_buffer[page_now-1].pop_front();
        }
        last_str = "";
        erase();
        mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
        for (int i = 0; i < page_arr[page_now-1].size(); i++){
            move(i+1,0);
            printl(page_arr[page_now-1][i],i,1);
        }
        pos_y--;
    }
    else;
    refresh();
    if (ZH_CH_BIT==0){
        C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y);
    }
    ZH_CH_BIT = 0;
    SetPos(pos_x,pos_y -  (page_now-1)*(page_y-2)+1);
}

int easyhtmleditor::default_(char ch2){
    char save[50]="\0";
    char ch[3]="\0";
    char ch1 = '0';         
    char ch3 = '0';
     //sudo apt-get install language-pack-zh-han* 中文字体
                        //中文 
    int input_num = 0;
    int num = 0;
    int bit_zhCN = 0;
    int bit_c = 0;
    string input_str;
    if(-128<=ch2&&ch2<=-1){
        ch1=getch();
        ch3 =getch();
        ch[0]=ch2;
		ch[1]=ch1;   
        ch[2]=ch3;                      
        mvprintw(pos_y-(page_now-1)*(page_y-2)+1,pos_x,"%c%c%c",ch[0],ch[1],ch[2]);                
        pos_x+=3;                            
        move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);
        refresh();
        bit_zhCN = 1;
	}
    else {
        input_num++;
        int mid = 0;
        int left = word[0];
        int right = word[word.size()-1];     
        if (ch2 < left){
            return 1;
        }						                       
        for (int i = 0; i < word.size(); i++){
            if (left==0&&right==0){
                return 1;
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
    }
    if (bit_c | bit_zhCN){
        if (pos_x==1&&pos_y-  (page_now-1)*(page_y-2)>page_arr[page_now-1].size()){
            if (bit_c){
                input_str.push_back(ch2);
                page_arr[page_now-1] .push_back(input_str);
            }
            else if(bit_zhCN){
                input_str.push_back(ch[0]);
                input_str.push_back(ch[1]);
                input_str.push_back(ch[2]);
                page_arr[page_now-1].push_back(input_str);
            }
            else;                                    
                input_str.clear();
        }
        else if(pos_x==1&&pos_y -  (page_now-1)*(page_y-2)<=page_arr[page_now-1].size()){
            if (bit_c){
                    page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin(),ch2);
                    move(pos_y -  (page_now-1)*(page_y-2)+1,0);
                    printw("%s",page_arr[page_now-1][pos_y - (page_y-2)*(page_now-1)].c_str());
            }
            else if(bit_zhCN){
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin(),ch[0]);
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+1,ch[1]); 
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+1,ch[2]);   
                move(pos_y -  (page_now-1)*(page_y-2)+1,0);
                printl(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)],0,0);                               
                move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x+1);                                            
                refresh();
            }
        }                 
        else if(pos_y-  (page_now-1)*(page_y-2)<=page_arr[page_now-1].size()&&pos_x<=page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].size()){                                    
            num = int(pos_x);
            if (bit_c){                                
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num-1,ch2);
                move(pos_y -  (page_now-1)*(page_y-2)+1,0);                                
                clrtoeol();
                move(pos_y -  (page_now-1)*(page_y-2)+1,0);
                printw("%s",page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)].c_str());
            }
            else if (bit_zhCN){
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num-1,ch[0]);
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num+1-1,ch[1]);
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].insert(page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].begin()+num+2-1,ch[2]);
                move(pos_y -  (page_now-1)*(page_y-2)+1,0);                                
                clrtoeol();
                move(pos_y -  (page_now-1)*(page_y-2)+1,0);
                printl(page_arr[page_now-1][pos_y-(page_now-1)*(page_y-2)],0,0);
            }
            refresh();
        }
        else if(pos_x > page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].size()&&pos_y -  (page_now-1)*(page_y-2)<=page_arr[page_now-1].size()){
            if (bit_c){
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].push_back(ch2);
            }
            else if (bit_zhCN){
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].push_back(ch[0]);
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].push_back(ch[1]);
                page_arr[page_now-1][pos_y -  (page_now-1)*(page_y-2)].push_back(ch[2]);
            }
        }  
        if (bit_c){
            string code_compl = cc2.Lexical_analysis(ch2,pos_y-(page_now-1)*(page_y-2),last_x,ret_fileread1,page_y,page_x);
            if (last_x-1  <= cc2.c_str.size()){   
                if (code_compl[code_compl.length()-1]!=ch2){
                    SetPos(0,pos_y - (page_now-1)*(page_y-2)+1);   
                        clrtoeol();                                
                        page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)].clear();
                        last_str+=code_compl;                            
                        page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)] = last_str ;
                        SetPos(0 ,pos_y - (page_now-1)*(page_y-2)+1);    
                        printw("%s",page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)].c_str());
                        C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y); 
                        pos_x = page_arr[page_now-1][pos_y - (page_now-1)*(page_y-2)].size(); 
                        mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
                        SetPos(pos_x,pos_y -  (page_now-1)*(page_y-2)+1);     
                        refresh();                         
                        return 1;
                }
            }               
        }                                 
    }
    if (bit_c){
        C3.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y); 
    }
    mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");                            
    move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x);	
    refresh();
    return 0;
}