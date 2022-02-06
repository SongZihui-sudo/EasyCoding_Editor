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
    	string        	  	str;
    	int 		  	ch1 = 0;
    	char 		  	ch2 ;
    	int 		  	num = 0;
    	string        		Parr_str;
    	int           		l_ret = -1;
	int           		i = 0;
	int           		key_fd  = 0;
	int           		enter_num = 0;
	struct 	      		input_event key_event  = {0};
	int			input_num = 0;

	cbreak();                     //开启cbreak模式，除 DELETE 或 CTRL 等仍被视为特殊控制字元外一切输入的字元将立刻被一一读取
 	nonl();                       //用来决定当输入资料时，按下 RETURN 键是否被对应为 NEWLINE 字元
 	noecho();                     //echo() and noecho(): 此函式用来控制从键盘输入字元时是否将字元显示在终端机上
 	keypad(stdscr,true);          //当开启 keypad 後, 可以使用键盘上的一些特殊字元, 如上下左右>等方向键
	move(1,0);
	while(ch2 = getch()){
		//printf("key asill %d\n", ch2);
		switch (ch2){
            		case BACKSPACE:
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
                    			SetPos(pos_x,pos_y -  (page_now-1)*page_y+1);
                    			if (num<page_arr[page_now-1][pos_y -  (page_now-1)*page_y].size()&&pos_y- (page_now-1)*page_y<=page_arr[page_now-1].size()){
                        			Parr_str =page_arr[page_now-1][pos_y -  (page_now-1)*page_y].substr(num);
                        			page_arr[page_now-1][pos_y -  (page_now-1)*page_y].erase(pos_x);
                        			page_arr[page_now-1][pos_y -  (page_now-1)*page_y] += Parr_str;
                    			}
                    			else if(num==page_arr[page_now-1][pos_y -  (page_now-1)*page_y].size()&&pos_y- (page_now-1)*page_y<=page_arr[page_now-1].size()){
                        			Parr_str = page_arr[page_now-1][pos_y-(page_now-1)*page_y][page_arr[page_now-1][pos_y-(page_now-1)*page_y].length()-1];
                        			page_arr[page_now-1][pos_y -  (page_now-1)*page_y].pop_back();
                    			}
                    			else;
                   			SetPos(0,pos_y -  (page_now-1)*page_y+1);
                    			clrtoeol();
                    			SetPos(0,pos_y -  (page_now-1)*page_y+1);
                    			printw("%s",page_arr[page_now-1][pos_y -  (page_now-1)*page_y].c_str());
                    		}
                		else if(pos_x == 0 && pos_y -  (page_now-1)*page_y == 0){
                    			pos_x = 0;
                   			last_x = 0;
                    			pos_y = (page_now-1)*page_y;
	               		}
                		else if(pos_x==0){
                    			pos_x = page_arr[page_now-1][pos_y-1 -  (page_now-1)*page_y].size();//  out_data[pos_y-1].size();
                    			page_arr[page_now-1][pos_y-1 -  (page_now-1)*page_y] += page_arr[page_now-1][pos_y -  (page_now-1)*page_y]; //out_data[pos_y];
                    			page_arr[page_now-1].erase(page_arr[page_now-1].begin()+pos_y -  (page_now-1)*page_y);
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
                		C3.Lexical_analysis(page_arr[page_now-1]);
                    		SetPos(pos_x,pos_y -  (page_now-1)*page_y+1);
                    		break;
                //回车
                    case ENTER:
                        last_str = "";
                	num = int(pos_y) -  (page_now-1)*(page_y-1);
                	if (pos_x>=page_arr[page_now-1][pos_y -  (page_now-1)*page_y].size()){
               		     	page_arr[page_now-1].insert(page_arr[page_now-1].begin()+num+1,"");
               	    	}
                    	else{
                    	    	str = page_arr[page_now-1][pos_y -  (page_now-1)*page_y].substr(pos_x);
                    	    	page_arr[page_now-1][pos_y -  (page_now-1)*page_y].erase(pos_x);
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
                	C3.Lexical_analysis(page_arr[page_now-1]);
                	pos_x = 0;
                	last_x = 0;
                	pos_y++;
                	if (pos_y>=page_y*(page_now)){
                    	    	pos_y--;
                	}
                	else{
                    	    	SetPos(pos_x,pos_y-(page_now-1)*page_y+1);
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
                    	page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num,' ');
                    	page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num+1,' ');
                    	page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num+2,' ');
                    	page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num+3,' ');
                    	page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num,' ');
                   	page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num+1,' ');
                    	page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num+2,' ');
                    	page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num+3,' ');
                    	SetPos(0,pos_y -  (page_now-1)*page_y+1);
                    	clrtoeol();
                    	SetPos(0,pos_y -  (page_now-1)*page_y+1);
                    	//cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y];
                    	printw("%s",page_arr[page_now-1][pos_y -  (page_now-1)*page_y].c_str());
                    	C3.Lexical_analysis(page_arr[page_now-1]);                                
                    	SetPos(pos_x,pos_y -  (page_now-1)*page_y+1);
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
                    	page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num,' ');    
                    	SetPos(0,pos_y -  (page_now-1)*page_y+1);
                    	clrtoeol();
                    	SetPos(0,pos_y -  (page_now-1)*page_y+1);
                    	printw("%s",page_arr[page_now-1][pos_y -  (page_now-1)*page_y].c_str());
                    	C3.Lexical_analysis(page_arr[page_now-1]);                                
                    	SetPos(pos_x,pos_y -  (page_now-1)*page_y+1);
                    	refresh();
			break;
                case PAGE_UP:
                        if (page_now==1){
                           	 page_now = page_now;
                        }
                        else{
                        	page_now--;
                            	pos_y= pos_y - page_y;
                        }
                        erase();	
			mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
                        for (int i = 0; i < page_arr[page_now-1].size(); i++){
                            	//cout<<page_arr[page_now-1][i]<<endl;
				move(i+1,0);
				printw("%s",page_arr[page_now-1][i].c_str());
                        }
                        C3.Lexical_analysis(page_arr[page_now-1]);     
                        //move(page_y,page_x-20);
                        //cout<<"page_y"<<page_now;  
                        mvprintw(page_y-1,page_x-10,"Page:%d",page_now);
			SetPos(0,1);
                        if (exact_buffer.size()){
                            	for (int i = 0; i < exact_buffer.size(); i++){
                                	exact_buffer.pop();
                        	}
                        }
                        else;
			refresh();
                        break;
                    case PAGE_DOWN:
			mvprintw(1,0,"OK1");
                        if (page_now<=page_y&&page_y){ 
                           	page_now++;
                            	pos_y+=page_y;
				mvprintw(1,0,"OK2");           
                        }
                        else{
				mvprintw(1,0,"OK3");
                            	page_now++;
                            	page_y++;
                            	pos_y+=page_y;
                            	page_arr.push_back({""});
                            	pos_x = 0;
				mvprintw(1,0,"OK4");
                        }
			mvprintw(1,0,"OK5");
                        erase();
			mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
                        mvprintw(1,0,"%d",page_arr[page_now-1].size());
			for (int i = 0; i < page_arr[page_now-1].size(); i++){
				move(i+1,0);
				printw("%s",page_arr[page_now-1][i].c_str());
                        }
			mvprintw(1,0,"OK6");
			if(!page_arr.empty())
                        	C3.Lexical_analysis(page_arr[page_now-1]);
                        else;
			move(page_y,page_x-20);
                        cout<<"page_y"<<page_now;
                        mvprintw(page_y-1,page_x-10,"Page:%d",page_now);
                        move(1,0);
                        if (exact_buffer.size()){
                            	for (int i = 0; i < exact_buffer.size(); i++){
                                	exact_buffer.pop();
                            	}   
                        }
			mvprintw(1,0,"OK7");
			refresh();
                        break;
                    	//上
                    	case UP:
                        	if (pos_y <= (page_now-1)*page_y){
                            		pos_y = pos_y;
                            		break;
                        	}
                        	else{
                            		if (pos_y){
                                		pos_y--;
                            		}
                            		else;
                        	}
                        	//move(page_y,page_x-10);
                        	mvprintw(page_y,page_x-10,"Lines:%d",pos_y);
                        	pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y].size();
                        	last_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y].size();
                        	move(pos_y -  (page_now-1)*page_y+1,pos_x);
				refresh();
                        	break;   
                    	//下
                    	case DOWN:
                        	if (pos_y-  (page_now-1)*page_y>=page_arr[page_now-1].size()-1);
                        	else pos_y++;
                        	//move(page_y,page_x-20);
                        	mvprintw(page_y-1,page_x-10,"Lines:%d",pos_y);
                        	pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y].size();
                        	move(pos_y -  (page_now-1)*page_y+1,pos_x);
				refresh();
                        	break;
                    	//左
                    	case LEFT:
                        	if (pos_x){
                            		pos_x--;
                            		last_x--;
                        	}
                        	else;
                        	//move(page_y,page_x-30);
                        	//cout<<pos_x<<"th";           
                        	mvprintw(page_y-1,page_x-10,"%dth",pos_x);                        
                        	move(pos_y -  (page_now-1)*page_y+1,pos_x);
				refresh();
                        	break;
                    	//右
                    	case RIGHT:
                        	if (pos_x>=page_arr[page_now-1][pos_y-  (page_now-1)*page_y].size()+1) pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y].size()+1;
                        	else{
                            		pos_x++;
                            		last_x++;                    
                        	}
                        	//move(page_y,page_x-30);
                        	mvprintw(page_y-1,page_x-10,"%dth",pos_x);
                        	move(pos_y -  (page_now-1)*page_y+1,pos_x);
				refresh();
                        	break;     
                    	case ESC:
				nl();
				echo();
				nocbreak();
				endwin();
                        	return true;
                    	default:     
				input_num++;
                        	int bit_c = 0;
                        	string input_str;
                        	int mid = 0;
                        	int left = word[0];
                        	int right = word[word.size()-1];                            
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
						if(input_num==1){
							mvprintw(pos_x-1,pos_y+1," ");
						}
                                		break;
                            		}
                        	}
                        	if (bit_c){
                            		if (pos_x==1&&pos_y-  (page_now-1)*page_y>page_arr[page_now-1].size()){
                                		input_str.push_back(ch2);
                               	 		page_arr[page_now-1] .push_back(input_str);
                                		input_str.clear();
                            		}
                            		else if(pos_x==1&&pos_y -  (page_now-1)*page_y<=page_arr[page_now-1].size()){
                                		page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin(),ch2);
                                		move(pos_y -  (page_now-1)*page_y+1,0);
                                		printw("%s",page_arr[page_now-1][pos_y - page_y*(page_now-1)].c_str());
						refresh();
                            		}                 
                            		else if(pos_y-  (page_now-1)*page_y<=page_arr[page_now-1].size()&&pos_x<=page_arr[page_now-1][pos_y -  (page_now-1)*page_y].size()){
                                		num = int(pos_x);
                                		page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num-1,ch2);
                                		move(pos_y -  (page_now-1)*page_y+1,0);
                                		clrtoeol();
                                		move(pos_y -  (page_now-1)*page_y+1,0);
                                		printw("%s",page_arr[page_now-1][pos_y - (page_now-1)*page_y].c_str());
						refresh();
                            		}
                            		else if(pos_x > page_arr[page_now-1][pos_y -  (page_now-1)*page_y].size()&&pos_y -  (page_now-1)*page_y<=page_arr[page_now-1].size()){
                                		page_arr[page_now-1][pos_y -  (page_now-1)*page_y].push_back(ch2);
                            		}
                            		else;  
                            	/*
                            		string code_compl = cc2.Lexical_analysis(ch2,pos_y -  (page_now-1)*page_y,last_x);
                            		if (last_x-1  <= cc2.c_str.size()){   
                                		if (code_compl[code_compl.length()-1]!=ch2){
                                    			SetPos(0,pos_y - (page_now-1)*page_y);   
                                    			printf("\033[K");                                
                                    			page_arr[page_now-1][pos_y - (page_now-1)*page_y].clear();
                                    			last_str+=code_compl;                            
                                    			page_arr[page_now-1][pos_y - (page_now-1)*page_y] = last_str ;
                                    			SetPos(0 ,pos_y - (page_now-1)*page_y);    
                                    			//cout<<page_arr[page_now-1][pos_y - (page_now-1)*page_y];
                                    			printf("%s",page_arr[page_now-1][pos_y - (page_now-1)*page_y].c_str());
                                    			C3.Lexical_analysis(page_arr[page_now-1]); 
                                    			pos_x = page_arr[page_now-1][pos_y - (page_now-1)*page_y].size(); 
                                    			SetPos(pos_x,pos_y -  (page_now-1)*page_y);                              
                                    			break;
                                		}
                                		else;
                                
                            		}       
                            		else;  */                       
                            		C3.Lexical_analysis(page_arr[page_now-1]);                                
                            		if(input_num==1)
						move(pos_y -  (page_now-1)*page_y+1,pos_x-1);
					else
						move(pos_y -  (page_now-1)*page_y+1,pos_x);
                        	}  
                        		break;
			    }
    	}
	printf("quit/n");
	return 0;
}
