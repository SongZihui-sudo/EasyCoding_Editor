#include "../include/EasyCodingEditor.h"
#include<stdio.h>
#include "../include/Code_highlighting.h"
#include "../include/Code_completion.h"
#include <cstring>
#include "../include/Article_device.h"
#include "../include/sql.h"

using namespace edt;
using namespace std;
using namespace cht;
using namespace cct;

cht::Code_highlighting C;
cct::Code_completion cc;

//打开文件
bool easyhtmleditor::open_files(string filename){
    fstream out;
    int i = 0;
    int j = 0;
	int line_num = 0;
    out.open(filename);
    string file_data;
    if (out){
        while (getline(out,file_data)){
            if (i<(page_y-1)){
				//mvprintw(i+1,0,"%s",file_data.c_str()); 
                for (int n = 0; n < file_data.size(); ){
                    if (file_data[n]<=-1&&file_data[n]>=-128){
                    	mvprintw(i+1,n,"%c%c%c",file_data[n],file_data[n+1],file_data[n+2]);                                                                   
                        n+=3;
                        ZH_CH_BIT = 1;
                    }
                    else{                                            
                        mvprintw(i+1,n,"%c",file_data[n]);
                        n++;
                    }                                            
                    move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x+1);                                            
                    refresh();
                }
				out_data.push_back(file_data);
            }
            else{
                out_data.push_back(file_data);  
            }
            if ((i%(page_y-1))==0&&i!=0){
                page_arr.push_back(out_data);
                j++;
                out_data.clear();
            }
            else;
            i++;
        }
    }
    else{
        SetPos(2,page_y-2);
        C.Set_color(RB);
        printw("open files error!!!");
		C.ReSetColor();
		refresh();
        return false;
    }      
    page = j;
    if (page<=1){
        page_arr.push_back(out_data);
    }
    else if (page*(page_y-1) < i){
        page_arr.push_back(out_data);
    }
    else;
    C.Lexical_analysis(page_arr[0],ret_fileread2,pos_y);
    SetPos(0,0);
	refresh();
    return true;
}
//设置光标位置
void easyhtmleditor::SetPos( int  x , int  y ){
	move(y,x);
	//printf("\033[%d;%dH", (y), (x));
}
//命令行
int easyhtmleditor::commander(int argc,char* argv[]){
	if (argc>1){
		string cmd = argv[1];
        if (cmd == "-v"){
            printf("EW:简·编辑器 Linux version:1.0\n");
            return 0;
        }
        else if(cmd == "-h"){
			readout_emakefile();
			Article_device_run(argv[2]);
            return 0;
        }
		else if(cmd[0]!='-'){
			initscr();
			string key_words = argv[1];
			string language;
        	language = key_words;
        	int bit = 0;
        	for (int i = language.size(); i >0 ; i--){
            	if (language[i] == '.'&& i!=0&&i!=1){
                	bit = i;
                	break;
            	}
            	else;
        	}
        	language = language.substr(bit+1,language.size()-1);
        	//ret_fileread2 = C.read_setting_files(language);
			if (language == "c" || language == "cpp"){
				ret_fileread2 = select("../data/data.db","HIGHLITE_C");
        		ret_fileread1 = select("../data/data.db","COMPANY");
			}
			else if (language == "eh" || language == "e"){
				ret_fileread2 = select("../data/data.db","HIGHLITE_E");
				ret_fileread1 = select("../data/data.db","COMPLETE_E");
			}
			else if (language == "h" || language == "html"){
				ret_fileread2 = select("../data/data.db","HIGHLITE_H");
				ret_fileread1 = select("../data/data.db","COMPLETE_H");
			}
        	open_files(key_words);
        	Edit_kernal();
			commander(0,argv);
		}
        else{
            printf("EW:找不到命令参数%s\n",cmd.c_str());
            return -1;
        }
	}
	else{
    	initscr();
    	char 		input_c[5];//C风格字符串
    	char 		key_words_c[5];
    	//C++ String
    	string 		language;
		initscr();
    	while(true){    
			mvprintw(2,10,"____________________  ");
			mvprintw(3,10,"\\_   _____/\\_   ___ \\");
			mvprintw(4,10," |    __)_ /    \\  \\/");
			mvprintw(5,10," |        \\     \\____");
			mvprintw(6,10,"/_______  / \\______  /");
			mvprintw(7,10,"        \\/         \\/");
    	//初始化字符
    		SetPos(page_x/2-5,int(page_y)/2-2);
    		printw("EasyCodingEditor(Linux)");
    		SetPos(page_x/2-5,int(page_y/2-1));
    		printw("Version v1.0");
    		SetPos(page_x/2-5,int(page_y/2));
    		printw("Help");
    		SetPos(page_x/2-5,int(page_y/2+1));
    		printw("Edit mode i | a");
    		SetPos(page_x/2-5,int(page_y/2+2));
    		printw("Save and quit wq");
			box(stdscr,'|','-');
    		//refresh();
        	SetPos(1,page_y-3);
        	printw(":");
			//refresh();
			scanw("%s",&input_c);
			string input(input_c);
        	if (input == key[0]){
        		printw("NOW YOU WILL EXIT WHIHOUT SAVE!!!");
	    		refresh();
        		return -1;
    		}
			else if(input == key[6]){
            	erase();
            	for (int i = 0; i < page_arr[page_now-1].size(); i++){
					//mvprintw(i+1,0,"%s",page_arr[page_now-1][i]);
					for (int i = 0; i < page_arr[page_now-1].size(); i++){
                        for (int n = 0; n < page_arr[page_now-1][i].size(); ){
                            if (page_arr[page_now-1][i][n]<=-1&&page_arr[page_now-1][i][n]>=-128){
                                mvprintw(i+1,n,"%c%c%c",page_arr[page_now-1][i][n],page_arr[page_now-1][i][n+1],page_arr[page_now-1][i][n+2]);                                                                   
                                n+=3;
                            }
                            else{                                            
                                mvprintw(i+1,n,"%c",page_arr[page_now-1][i][n]);
                                n++;
                            }                                            
                            move(pos_y -  (page_now-1)*(page_y-2)+1,pos_x+1);                                            
                            refresh();
                        }
                    }	
            	}
            	C.Lexical_analysis(page_arr[page_now-1],ret_fileread2,pos_y);
            	SetPos(0,0);
            	Edit_kernal();
        	}
			else if (input == key[9]){
					erase();
					system("sudo chmod 777 ../../README.txt");
            		if (open_files("../../README.txt")){
                		Edit_kernal();
            		}
            	else;
        	}
			else;
			SetPos(1,page_y-2);
			printw(":");
			refresh();
        	//getstr(key_words_c);
    		//printw("%s",key_words_c);
        	scanw("%s",&key_words_c);
			string key_words(key_words_c,key_words_c+strlen(key_words_c));
		//cout<<input<<" "<<key_words;
			if(input == key[4]){
            	save_files(key_words,page_arr);
            	return 1;
        	}
        	else if(input == key[1] || input == key[2]){
            		//printw("Edit mode test\n");
                        //refresh();
				char ch;
            	language = key_words;
            	if (language == "c" || language == "cpp"){
					ret_fileread2 = select("../data/data.db","HIGHLITE_C");
        			ret_fileread1 = select("../data/data.db","COMPANY");
				} 
				else if (language == "eh" || language == "e"){
					ret_fileread2 = select("../data/data.db","HIGHLITE_E");
					ret_fileread1 = select("../data/data.db","COMPLETE_E");
				}
				else if (language == "h" || language == "html"){
					ret_fileread2 = select("../data/data.db","HIGHLITE_H");
					ret_fileread1 = select("../data/data.db","COMPLETE_H");
				}
            	//while((getchar()!='\n'));
            	printw("Edit mode\n");
				refresh();
				CLEAR();
				Edit_kernal();
        		}
        	else if(input == key[5]){
            	CLEAR();
            	language = key_words;
            	int bit = 0;
            	for (int i = language.size(); i >0 ; i--){
            		if (language[i] == '.'&& i!=0&&i!=1){
                		bit = i;
                		break;
            		}
            		else;
        		}
            	language = language.substr(bit+1,language.size()-1);
            	if (language == "c" || language == "cpp"){
					ret_fileread2 = select("../data/data.db","HIGHLITE_C");
        			ret_fileread1 = select("../data/data.db","COMPANY");
				}
				else if (language == "eh" || language == "e"){
					ret_fileread2 = select("../data/data.db","HIGHLITE_E");
					ret_fileread1 = select("../data/data.db","COMPLETE_E");
				}
				else if (language == "h" || language == "html"){
					ret_fileread2 = select("../data/data.db","HIGHLITE_H");
					ret_fileread1 = select("../data/data.db","COMPLETE_H");
				}
            	if(open_files(key_words)){
                	Edit_kernal();
            	}
            	else;
        	}
        	else if(input == key[7]){
            		save_files(key_words,page_arr);
            		cin.sync();
            		string cmd;
            		cout<<"\n";
            		getline(cin,cmd);
            		const char* c_command;
            		c_command = cmd.c_str();
            		system(c_command);
        	}
        	else if(input == key[3]){
            		find(key_words);
        	}
        	else if(input == key[8]){
					readout_emakefile();
					Article_device_run(key_words);
            		return 1;
        	}
        	else{
            		SetPos(0,page_y);
            		C.Set_color(RB);
            		mvprintw(page_y-2,1,"command %s,%s not find!!!",input.c_str(),key_words.c_str());
					C.ReSetColor();
        	}
			refresh();
    	}
	}
    	return 0;
	}
//查找
bool easyhtmleditor::find(string finding){
    vector <int> state;
    for (int i = 0; i < page_arr[page_now-1].size(); i = i+2){
        int k = 0;int n = 0;
		while(page_arr[page_now-1][i][k]!='\0'&&finding[n]!='\0'){
			if(page_arr[page_now-1][i][k]==finding[n]){
				k++;
				n++;
			}
			else{
				k=k-n+1;
				n=0;
			}
		}
		if(finding[n]=='\0'){
			state.push_back(i);
		}  
		else;  
    }
    SetPos(0,page_y-2);
    clrtoeol();
	mvprintw(0,pos_y-2,"find","Lines:%d",state.size());
    SetPos(0,0);
    return false;
}
//保存
bool easyhtmleditor::save_files(string filename,deque < deque <string> > save_Data){
    ofstream in;
    in.open(filename);
    if (in){
       for (int i = 0; i < save_Data.size(); i++){
            for (int j = 0; j < save_Data[i].size(); j++){
                in<<save_Data[i][j]<<"\n";
            }
        }
    }
    else{
        cerr<<"can save the files!!!"<<endl;   
    }
    return true;
}

void easyhtmleditor::print_size(){
    //定义winsize 结构体变量
    struct winsize size;
    //TIOCSWINSZ命令可以将此结构的新值存放到内核中
    ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
    page_x = size.ws_col;
    page_y = size.ws_row;
}

int easyhtmleditor::printg(deque <string> print_page){
    for (int i = 0; i < print_page.size(); i++){
        printf("%s\n",print_page[i].c_str());
    }
    return 0;
}

/*
1 2 3 4 5
1 2 4 5 
*/
