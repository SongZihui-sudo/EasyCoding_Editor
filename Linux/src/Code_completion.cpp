#include "../include/Code_completion.h"
#include <vector>
#include "../include/EasyCodingEditor.h"
#include "../include/Code_highlighting.h"

using namespace cct;
using namespace edt;
using namespace cht;

edt::easyhtmleditor e2;
cht::Code_highlighting c2;

//读取文件
deque <string> Code_completion::read_outfiles(string language){
    if (language == "c" || language == "cpp"){
        fstream out_files_completion;
        out_files_completion.open("../Code_completion/c_setting.txt");
        if (out_files_completion){
            string out;
            while (getline(out_files_completion,out)){
                code_completion.push_back(out);
            }
        }
        else{
            cerr<<"Can not open the files!!!"<<endl;
            return code_completion;
        }
    }
    else;
    return code_completion;
}
//词法分析
string Code_completion::Lexical_analysis(char c,int pos_y,int pos_x,deque <string> file_data,int page_y,int page_x){
    code_completion = file_data;
    if (pos_x-1>c_str.size());
    else if (last_y!=pos_y){
        c_str = "";
        c_str.push_back(c);
    }
    else if(pos_y == last_y){
        c_str.push_back(c);
    }
    deque <int> state;
    for (int i = 1; i < code_completion.size(); i = i+2){
        int k = 0;int n = 0;
		while(code_completion[i][k]!='\0'&&c_str[n]!='\0'){
			if(code_completion[i][k]==c_str[n]){
				k++;
				n++;
			}
			else{
				k=k-n+1;
				n=0;
			}
		}
		if(c_str[n]=='\0'){
			state.push_back(i);
		}  //(k-n);     //主串中存在该模式返回下标号 
		else;     //主串中不存在该模式 
    }     
    if (!state.empty()){
        e2.SetPos(0,page_y);
        clrtoeol();
        refresh(); 
        e2.SetPos(0,page_y);
        for (int i = 0; i < state.size(); i++){
            c2.Set_color(YB);
            mvprintw(page_y-1,5*i,"%s ",code_completion[state[i]].c_str());    
            c2.ReSetColor();
            refresh();
        }
        if(state.size()==1){
            bit  = 1;
            return code_completion[state[0]+1];
        }    
    }
    else{
        mvprintw(0,page_x/2,"EasyCodingEditor(Linux) version1.0 ");
        if (bit){
            bit = 0;
            state.pop_back();
            return c_str;
        }
        e2.SetPos(0,e2.page_y);
        clrtoeol();
        return c_str;
    }
    last_y = pos_y;
    last_str = c_str;
    return c_str;
}