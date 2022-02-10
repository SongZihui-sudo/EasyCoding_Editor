#include "../include/Code_highlighting.h"
#include "../include/EasyCodingEditor.h"
#include <curses.h>
#include<string>

using namespace cht;
using namespace edt;

edt::easyhtmleditor e1;

//设置颜色
void Code_highlighting::Set_color(int color){
	int i;
	initscr();
  
	if(!has_colors()){
    	endwin();
    	fprintf(stderr,"Error - no color support on this terminal \n");
    	exit(1);
  	} 
  	if(start_color() != OK){
    	endwin();
    	fprintf(stderr,"Error -could not initialize colors\n");
    	exit(2);
  	} 
  
  	//erase();
  	//refresh();
  
  	init_pair(1,COLOR_RED,COLOR_BLACK);
  	init_pair(2,COLOR_BLUE,COLOR_BLACK);
  	init_pair(3,COLOR_GREEN,COLOR_BLACK);
  	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
  	init_pair(5,COLOR_BLACK,COLOR_BLACK);
  	init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
  	init_pair(7,COLOR_CYAN,COLOR_BLACK);
	init_pair(8,COLOR_WHITE,COLOR_BLACK);

	attroff(A_BOLD);

	attrset(COLOR_PAIR(color));
	
}

void Code_highlighting::ReSetColor(){
	Set_color(WB);
}

//词法分析
bool Code_highlighting::Lexical_analysis(deque <string> ready_highlight,deque <string>file_data,int pos_y){
	key_words2 = file_data;
	vector <cht::pos> postion;
    vector <int> state; 
	initscr();		
	for (int i = 0; i < ready_highlight.size(); i++){
		int bit = -1;	
		int num_tab = 0;
		for (int k = 0; k < ready_highlight[i].size(); k++){
			if (ready_highlight[i][k] == '\t'){
				num_tab++;
			}
			else{
				break;
			}
		}
			for (int j = 0; j <key_words2.size(); j++){
				bit = ready_highlight[i].find(key_words2[j]);
				if (bit!=-1){
					state.push_back(j);
					cht::pos p1;
					p1.x = bit+(num_tab*8);
					p1.y = i+1; 
					postion.push_back(p1);
					bit = 1;
				}
				else{
					;
				}
			}
			
		}
	for (int i = 0; i < state.size(); i++){
		if (state[i]){
			Set_color(BLB);
			mvprintw(postion[i].y,postion[i].x,"%s",key_words2[state[i]].c_str());
			ReSetColor();
			refresh(); 
		}
		else;   
	}
	postion.clear();
	state.clear();
	ready_highlight.clear();
	move(0,0);
    return false;
}