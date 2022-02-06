#include "../include/Code_highlighting.h"
#include "../include/EasyCodingEditor.h"

using namespace cht;
using namespace edt;

edt::easyhtmleditor e1;

//设置颜色
void Code_highlighting::Set_color(int wr,int wg,int wb,int br,int bg,int bb){
    	printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,br,bg,bb);	
        //\033[38表示前景，\033[48表示背景，三个%d表示混合的数
}
//rgb初始化
void Code_highlighting::rgb_init(){
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);		//输入句柄
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//输出句柄
	DWORD dwInMode, dwOutMode;
	GetConsoleMode(hIn, &dwInMode);						//获取控制台输入模式
	GetConsoleMode(hOut, &dwOutMode);					//获取控制台输出模式
	dwInMode |= 0x0200;									//更改
	dwOutMode |= 0x0004;
	SetConsoleMode(hIn, dwInMode);						//设置控制台输入模式
	SetConsoleMode(hOut, dwOutMode);					//设置控制台输出模式
}
//词法分析
bool Code_highlighting::Lexical_analysis(deque <string> ready_highlight){
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
			Set_color(1,186,200,0,0,0);
			cout<<key_words[state[i]];
			Set_color(255,255,255,0,0,0);	
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