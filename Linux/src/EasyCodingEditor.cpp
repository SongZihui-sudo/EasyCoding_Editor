#include "../include/EasyCodingEditor.h"
#include<stdio.h>
#include "../include/Code_highlighting.h"
#include "../include/Code_completion.h"
#include "../include/Markdown_parser.h"

using namespace edt;
using namespace std;
using namespace cht;
using namespace cct;
using namespace mpt;

cht::Code_highlighting C;
cct::Code_completion cc;
mpt::Markdown_parser mp;

//打开文件
bool easyhtmleditor::open_files(string filename){
    fstream out;
    int i = 0;
    int j = 0;
    out.open(filename);
    string file_data;
    if (out){
        while (getline(out,file_data)){
            if (i<page_y-2){
                cout<<file_data<<endl;
                out_data.push_back(file_data);  
            }
            else{
                out_data.push_back(file_data);  
            }
            if ((i%page_y-2)==0&&i!=0){
                page_arr.push_back(out_data);
                j++;
                out_data.clear();
            }
            else;
            i++;
        }
    }
    else{
        SetPos(0,page_y-1);
        C.Set_color(F_RED);
        cerr<<"open files error!!!"<<endl;
        C.resetFColor();	
        SetPos(0,0);
        return false;
    }      
    page = j;
    if (page<=1){
        page_arr.push_back(out_data);
    }
    else if (page*page_y-2 < i){
        page_arr.push_back(out_data);
    }
    else;
    C.Lexical_analysis(page_arr[0]);
    SetPos(0,0);
    return true;
}
//设置光标位置
void easyhtmleditor::SetPos( int  x , int  y ){
    printf("\033[%d;%dH", (x), (y));
}
//命令行
int easyhtmleditor::commander(){
    CLEAR();
    SetPos(page_x/2,int(pos_y/2-2));
    cout<<"EasyCoding编辑器";
    SetPos(page_x/2,int(page_y/2-1));
    cout<<"版本：v1.0";
    SetPos(page_x/2,int(page_y/2));
    cout<<"帮助";
    SetPos(page_x/2,int(page_y/2+1));
    cout<<"编辑 i | a";
    SetPos(page_x/2,int(page_y/2+2));
    cout<<"保存并退出wq";
    string input;
    string key_words;
    string language;
    while(true){    
        SetPos(0,page_y-1);
        for (int i = 0; i < 100; i++){
            cout<<" ";
        }
        SetPos(0,page_y-1);
        cout<<":";
        cin>>input;
        if (input == key[0]){
            cout<<"NOW YOU WILL EXIT WHIHOUT SAVE!!!"<<endl;
            return -1;
        }
        cin>>key_words;
        if(input == key[4]){
            save_files(key_words,page_arr);
            return 1;
        }
        else if(input == key[1] || input == key[2]){
            CLEAR();
            language = key_words;
            cc.read_outfiles(language);
            C.read_setting_files(language);
            creat_files();
        }
        else if(input == key[5]){
            CLEAR();
            language = key_words;
            int bit = 0;
            for (int i = 0; i < language.size(); i++){
                if (language[i] == '.'&& i!=0&&i!=1){
                    bit = i;
                    break;
                }
                else;
            }
            language = language.substr(bit+1,language.size()-1);
            C.read_setting_files(language);
            cc.read_outfiles(language);
            if(open_files(key_words)){
                creat_files();
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
        else if(input == key[6]){
            CLEAR();
            for (int i = 0; i < page_arr[page_now-1].size(); i++){
                cout<<page_arr[page_now-1][i]<<endl;
            }
            C.Lexical_analysis(page_arr[page_now-1]);
            SetPos(0,0);
            creat_files();
        }
        else if(input == key[3]){
            find(key_words);
        }
        else if(input == key[8]){
            deque <deque <string>> html;
            html = mp.syntax_conversion(mp.Lexical_analysis(page_arr),page_arr);
            save_files(key_words,html);
            return 1;
        }
        else if (input == key[9]){
            CLEAR();        
            if (open_files("../../readme.md")){
                creat_files();
            }
            else;
        }
        else{
            SetPos(0,page_y-1);
            C.Set_color(F_RED);
            cerr<<"command not find!!!"<<endl;
            C.resetFColor();
            SetPos(0,0);
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
    SetPos(0,page_y-1);
    for (int i = 0; i < 100; i++){
        cout<<" ";
    }
    cout<<"find"<<" "<<state.size()<<" Lines:";
    for (int i = 0; i < state.size(); i++){
        cout<<" "<<state[i];
    }
    SetPos(0,0);
    return false;
}
//创建编辑
bool easyhtmleditor::creat_files(){
    if (!out_data.empty());
    else{
        deque <string> write_page;
        write_page.push_back("");
        page_arr.push_back(write_page);
    }        
    string str;
    int ch1 = 0;
    char ch2 = 0;
    SetPos(0,0);
    int num = 0;        
    while (true){    
        if(ch2 = get_key()){
            SetPos(0,0);          
            string Parr_str;
            switch(ch2){
                //删除
                case 0x8:
                    if (cc.c_str.empty());
                    else{
                        cc.c_str.pop_back();
                    }
                    if (last_str.empty());
                    else{                                           
                        last_str.pop_back();
                    }

                    if (pos_x){                        
                        num = pos_x;
                        pos_x--;   
                        last_x--;                      
                        SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);
                        if (num<page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].size()&&pos_y- (page_now-1)*page_y-2<=page_arr[page_now-1].size()){
                            Parr_str =page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].substr(num);
                            page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].erase(pos_x);
                            page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2] += Parr_str; 
                        }
                        else if(num==page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].size()&&pos_y- (page_now-1)*page_y-2<=page_arr[page_now-1].size()){
                            Parr_str = page_arr[page_now-1][pos_y-(page_now-1)*page_y-2][page_arr[page_now-1][pos_y-(page_now-1)*page_y-2].length()-1];
                            page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].pop_back();
                        }
                        else;
                        SetPos(0,pos_y -  (page_now-1)*page_y-2);
                        for (int i = 0; i < 100; i++){
                            cout<<" ";
                        }
                        SetPos(0,pos_y -  (page_now-1)*page_y-2);
                        cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2];
                    }
                    else if(pos_x == 0 && pos_y -  (page_now-1)*page_y-2 == 0){
                        pos_x = 0;
                        last_x = 0;
                        pos_y = (page_now-1)*page_y-2;
                    }
                    else if(pos_x==0){
                        pos_x = page_arr[page_now-1][pos_y-1 -  (page_now-1)*page_y-2].size();//  out_data[pos_y-1].size();                    
                        page_arr[page_now-1][pos_y-1 -  (page_now-1)*page_y-2] += page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2]; //out_data[pos_y];
                        page_arr[page_now-1].erase(page_arr[page_now-1].begin()+pos_y -  (page_now-1)*page_y-2);
                        if (page_arr[page_now-1].size() < page_y-2&&exact_buffer.size()!=0){
                            page_arr[page_now-1].push_back(exact_buffer.top());
                            exact_buffer.pop();
                        }    
                        last_str = "";
                        CLEAR();
                        for (int i = 0; i < page_arr[page_now-1].size(); i++){
                            cout<<page_arr[page_now-1][i]<<endl;
                        }
                        pos_y--;
                    }      
                    else;   
                    SetPos(0,page_y-2);
                    cout<<"\n";
                    C.Lexical_analysis(page_arr[page_now-1]);                                
                    SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);
                    break;
                //回车
                case 0xD:     
                    last_str = "";                   
                    num = int(pos_y) -  (page_now-1)*page_y-2;
                    if (pos_x>=page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].size()){
                        page_arr[page_now-1].insert(page_arr[page_now-1].begin()+num+1,""); 
                    }         
                    else{
                        str = page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].substr(pos_x);
                        page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].erase(pos_x);
                        page_arr[page_now-1].insert(page_arr[page_now-1].begin()+num+1,str);
                    }
                    if (page_arr[page_now-1].size() > page_y-2){
                        exact_buffer.push(page_arr[page_now-1][page_arr[page_now-1].size()-1]);
                        page_arr[page_now-1].pop_back();
                    }       
                    CLEAR();
                    for (int i = 0; i < page_arr[page_now-1].size(); i++){
                        cout<<page_arr[page_now-1][i]<<endl;
                    }                    
                    C.Lexical_analysis(page_arr[page_now-1]);                                
                    pos_x = 0;
                    last_x = 0;                    
                    pos_y++;
                    if (pos_y>=page_y-2*(page_now)){
                        pos_y--;
                        break;
                    }
                    else{
                        SetPos(pos_x,pos_y-(page_now-1)*page_y-2);    
                    }
                    break;
                //TAB
                case 0x9:
                    if (cc.c_str.empty());
                    else{
                        cc.c_str.clear();
                        cc.c_str = "";
                        last_x = 0;
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
                    pos_x +=4;
                    page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].begin()+num,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].begin()+num+1,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].begin()+num+2,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].begin()+num+3,' ');
                    SetPos(0,pos_y -  (page_now-1)*page_y-2);
                    for (int i = 0; i < 30; i++){
                        cout<<" ";
                    }
                    SetPos(0,pos_y -  (page_now-1)*page_y-2);
                    cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2];
                    C.Lexical_analysis(page_arr[page_now-1]);                                
                    SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);                    
                    break;
                //空格
                case 0x20:
                    if (cc.c_str.empty());
                    else{
                        cc.c_str.clear();
                        cc.c_str = "";
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
                    page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].begin()+num,' ');    
                    SetPos(0,pos_y -  (page_now-1)*page_y-2);
                    for (int i = 0; i < 30; i++){
                        cout<<" ";
                    }
                    SetPos(0,pos_y -  (page_now-1)*page_y-2);
                    cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2];
                    C.Lexical_analysis(page_arr[page_now-1]);                                
                    SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);
                    break;
                case 0x21:
                    if (page_now==1){
                        page_now = page_now;
                    }
                    else{
                        page_now--;
                        pos_y= pos_y - page_y-2;
                    }
                    CLEAR();
                    for (int i = 0; i < page_arr[page_now-1].size(); i++){
                        cout<<page_arr[page_now-1][i]<<endl;
                    }
                    C.Lexical_analysis(page_arr[page_now-1]);     
                    SetPos(130,page_y-1);
                    cout<<"Page"<<page_now;                   
                    SetPos(0,0);
                    if (exact_buffer.size()){
                        for (int i = 0; i < exact_buffer.size(); i++){
                            exact_buffer.pop();
                        }
                    }
                    else;
                    break;
                case 0x22:
                    if (page_now<=page&&page){ 
                        page_now++;
                        pos_y+=page_y-2;           
                    }
                    else{
                        deque <string> space_line;
                        space_line.push_back("");
                        page_now++;
                        page++;
                        pos_y+=page_y-2;
                        page_arr.push_back(space_line);
                        pos_x = 0;
                    }
                    CLEAR();
                    for (int i = 0; i < page_arr[page_now-1].size(); i++){
                        cout<<page_arr[page_now-1][i]<<endl;
                    }
                    C.Lexical_analysis(page_arr[page_now-1]);  
                    SetPos(130,page_y-1);
                    cout<<"Page"<<page_now;
                    SetPos(0,0);
                    if (exact_buffer.size()){
                        for (int i = 0; i < exact_buffer.size(); i++){
                            exact_buffer.pop();
                        }
                    }
                    break;
                //上
                case 0x26: 
                    if (pos_y <= (page_now-1)*page_y-2){
                        pos_y = pos_y;
                        break;
                    }
                    else{
                        if (pos_y){
                            pos_y--;
                        }
                        else;
                    }
                    SetPos(140,page_y-1);
                    cout<<"Line:"<<pos_y; 
                    pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y-2].size();
                    last_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y-2].size();
                    SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);
                    break;   
                //下
                case 0x28: 
                    if (pos_y-  (page_now-1)*page_y-2>=page_arr[page_now-1].size()-1);
                    else pos_y++;
                    SetPos(140,page_y-1);
                    cout<<"Line:"<<pos_y; 
                    pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y-2].size();
                    SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);
                    break; 
                //左
                case 0x25: 
                    if (pos_x){
                        pos_x--;
                        last_x--;
                    }
                    else; 
                    SetPos(120,page_y-1);
                    cout<<pos_x<<"th";                
                    SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);
                    break;
                //右
                case 0x27: 
                    if (pos_x>=page_arr[page_now-1][pos_y-  (page_now-1)*page_y-2].size()) pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y-2].size();
                    else{
                        pos_x++;
                        last_x++;                    
                    } 
                    SetPos(120,page_y-1);
                    cout<<pos_x<<"th"; 
                    SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);
                    break;     
                //esc
                case 0x1B:
                    return true;
                default:                    
                    int bit = 0;
                    string input_str;
                    int mid = 0;
                    int left = word[0];
                    int right = word[word.size()-1];                            
                    for (int i = 0; i < word.size(); i++){
                        mid = (left+right)/2;
                        if (ch2>mid){
                            left = mid + 1;                            
                        }
                        else if(ch2<mid){
                            right = mid -1;
                        }
                        else{
                            bit =1; 
                            SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);                             
                            cout<<ch2;                            
                            pos_x++;
                            last_x++;
                            break;
                        }
                    }
                    if (bit){
                        if (pos_x==1&&pos_y-  (page_now-1)*page_y-2>page_arr[page_now-1].size()){
                            input_str.push_back(ch2);
                            page_arr[page_now-1] .push_back(input_str);
                            input_str.clear();
                        }
                        else if(pos_x==1&&pos_y -  (page_now-1)*page_y-2<=page_arr[page_now-1].size()){
                            page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].begin(),ch2);
                            SetPos(0,pos_y -  (page_now-1)*page_y-2);
                            cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2];
                        }                 
                        else if(pos_y-  (page_now-1)*page_y-2<=page_arr[page_now-1].size()&&pos_x<=page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].size()){
                            num = int(pos_x);
                            page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].begin()+num-1,ch2);
                            for (int i = 0; i < 100; i++){
                                cout<<" ";
                            }
                            SetPos(0,pos_y -  (page_now-1)*page_y-2);
                            cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2];
                        }
                        else if(pos_x > page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].size()&&pos_y -  (page_now-1)*page_y-2<=page_arr[page_now-1].size()){
                            page_arr[page_now-1][pos_y -  (page_now-1)*page_y-2].push_back(ch2);
                        }
                        else;      
                        string code_compl = cc.Lexical_analysis(ch2,pos_y -  (page_now-1)*page_y-2,last_x);
                        if (last_x-1  <= cc.c_str.size()){   
                            if (code_compl[code_compl.length()-1]!=ch2){
                                SetPos(0,pos_y - (page_now-1)*page_y-2);   
                                for (int i = 0; i < 100; i++){
                                    cout<<" ";
                                }                                  
                                page_arr[page_now-1][pos_y - (page_now-1)*page_y-2].clear();
                                last_str+=code_compl;                            
                                page_arr[page_now-1][pos_y - (page_now-1)*page_y-2] = last_str ;
                                SetPos(0 ,pos_y - (page_now-1)*page_y-2);    
                                cout<<page_arr[page_now-1][pos_y - (page_now-1)*page_y-2];
                                C.Lexical_analysis(page_arr[page_now-1]); 
                                pos_x = page_arr[page_now-1][pos_y - (page_now-1)*page_y-2].size(); 
                                SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);                              
                                break;
                            }
                        }                                
                        C.Lexical_analysis(page_arr[page_now-1]);                                
                        SetPos(pos_x,pos_y -  (page_now-1)*page_y-2);
                    }
                    else;
                    break;
            }
        }     
        else;
        sleep(10);  
    }
    return true;
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

/*
1 2 3 4 5
1 2 4 5 
*/