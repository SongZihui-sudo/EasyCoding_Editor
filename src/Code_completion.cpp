#include "../include/Code_completion.h"
#include <vector>
#include "../include/EasyCodingEditor.h"
#include "../include/Code_highlighting.h"
#include <conio.h>

using namespace cct;
using namespace edt;
using namespace cht;

edt::easyhtmleditor e2;
cht::Code_highlighting c2;

//读取文件
bool Code_completion::read_outfiles(string language){
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
            return false;
        }
    }
    else;
    return true;
}
//词法分析
int Code_completion::Lexical_analysis(char c,int pos_y){
    if (last_y!=pos_y){
        c_str.clear();
        c_str.push_back(c);
    }
    else{
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
    int size = 0;
    if (!state.empty()){
        e2.SetPos(0,39);
        for (int i = 0; i < 80; i++){
            cout<<" ";
        }
        e2.SetPos(0,39);
        for (int i = 0; i < state.size(); i++){
            c2.Set_color(255,215,0,0,0,0);
            cout<<code_completion[state[i]]<<" ";    
            c2.Set_color(255,255,255,0,0,0);
        }  
    }
    else{
        e2.SetPos(0,39);
        for (int i = 0; i < 100; i++){
            cout<<" ";
        }
        size = 0;            
        return 0;
    }
    last_y = pos_y;
    return 0;
}