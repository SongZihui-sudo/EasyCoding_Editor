#include "../include/Code_highlighting.h"
#include "../include/EasyCodingEditor.h"
#include <curses.h>

using namespace cht;
using namespace edt;

edt::easyhtmleditor e1;

//设置颜色
bool Code_highlighting::Set_color(int color){
    bool ret = true;
	int fore = color%8;	//取color的后3位
	int back = (color/8)*8;	//将color的后3位清空 (即取前3位)
	switch (fore)
	{
	case F_BLACK:std::cout<<"\033[30m";break;
	case F_RED:std::cout<<"\033[31m";break;
	case F_GREEN:std::cout<<"\033[32m";break;
	case F_YELLOW:std::cout<<"\033[33m";break;
	case F_BLUE:std::cout<<"\033[34m";break;
	case F_DPURPLE:std::cout<<"\033[35m";break;
	case F_WHITE:std::cout<<"\033[37m";break;
	default:ret = false;
	}
	switch (back)
	{
	case B_BLACK:std::cout<<"\033[40m";break;
	case B_RED:std::cout<<"\033[41m";break;
	case B_GREEN:std::cout<<"\033[42m";break;
	case B_BROWN:std::cout<<"\033[43m";break;
	case B_BLUE:std::cout<<"\033[44m";break;
	case B_WHITE:std::cout<<"\033[47m";break;
	default:ret = false;
	}
	return ret;
}

void Code_highlighting::resetFColor(){
	printw("\033[39m");
	refresh();
}

void Code_highlighting::resetBColor(){
	printw("\033[49m");
	refresh();
}

//词法分析
bool Code_highlighting::Lexical_analysis(deque <string> ready_highlight){
	initscr();
	vector <int> state;
	vector <cht::pos> postion;
	for (int i = 0; i < ready_highlight.size(); i++){
		int bit_num = 0;
		int bit_y = 0;
		int bit_x = 0;
		int bit = 0;
		for (int j = 0; j < key_words.size(); j++){
			int k = 0;
			int n = 0;
			int y = 0;
			while(ready_highlight[i][k]!='\0'&&key_words[j][n]!='\0'){
				if(ready_highlight[i][k]==key_words[j][n]){
					k++;
					n++;
				}
				else{
					k=k-n+1;
					n=0;
				}
			}
		if(key_words[j][n]=='\0'){
			state.push_back(j);
			cht::pos p1;
			p1.y = i;
			p1.x = k - n;
			postion.push_back(p1);
		}  //(k-n);     //主串中存在该模式返回下标号 
		else;     //主串中不存在该模式 
		}
	}
	for (int i = 0; i < state.size(); i++){
		if (state[i]){
			e1.SetPos(postion[i].x,postion[i].y);
			Set_color(F_BLUE);
			//cout<<key_words[state[i]];
			printw("%s",key_words[state[i]].c_str());
			refresh();
			resetFColor();
		}
		else;
	}
	postion.clear();
	state.clear();
	ready_highlight.clear();
    return false;
}
//读取文件
bool Code_highlighting::read_setting_files(string language){
	if (language == "c" || language == "cpp"){
		fstream out_setting;
		out_setting.open("../Code_highlighting/c_setting.txt");
		string out_str;
		if (out_setting){
			while (getline(out_setting,out_str)){
				key_words.push_back(out_str);
			}
		}
		else{
			cerr<<"can not open the files!!!"<<endl;
			return false;
		}
	}
	else;
	return true;
}
