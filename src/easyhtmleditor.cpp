#include "../include/easyhtmleditor.h"
#include<stdio.h>
#include <conio.h>
#include <Windows.h>

using namespace edt;
using namespace std;

//打开文件
bool easyhtmleditor::open_files(string filename){
    fstream out;
    out.open(filename);
    string file_data;
    if (out){
        while (getline(out,file_data)){
            cout<<file_data<<endl;
            out_data.push_back(file_data);
        }
        for (int i = 0; i < 29 - pos_y; i++){
            cout<<"~"<<endl;
        }
    }
    else{
        cerr<<"open files error!!!"<<endl;
        return false;
    }
    return true;
}
//设置光标位置
void easyhtmleditor::SetPos( short int  x , short int  y ){
        COORD  point = {  x ,  y  }; //光标要设置的位置x,y
        HANDLE  HOutput = GetStdHandle( STD_OUTPUT_HANDLE ); //使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
        SetConsoleCursorPosition(HOutput, point); //设置光标位置
}
//命令行
int easyhtmleditor::commander(){
    int nHeight = GetSystemMetrics(SM_CYSCREEN); //屏幕高度
    string input;
    string key_words;
    while(true){
        if (pos_y){
            SetPos(0,pos_y+1);
        }
        else{
            for (int i = 0; i < 28; i++){
                cout<<"~"<<endl;
            }
        }
        cout<<":";
        cin>>input>>key_words;
        if (input == key[0])
        {
            cout<<"NOW YOU WILL EXIT WHIHOUT SAVE!!!"<<endl;
            return -1;
        }
        else if(input == key[4]){
            save_files(key_words,out_data);
            return 1;
        }
        else if(input == key[1] || input == key[2]){
            system("cls");
            creat_files();
        }
        else if(input == key[5]){
            system("cls");
            if(open_files(key_words)) 
                creat_files();
            else;
        }
        else if(input == key[3]){
            find(key_words);
        }
        else{
            cerr<<"command not find!!!"<<endl;
        }
    }
    return 0;
}
//查找
bool easyhtmleditor::find(string finding){
    int bit = 0;
    for (int i = 0; i < out_data.size(); i++){
        for ( int j = 0; j < out_data[i].size(); j++){
            for (int k = 0; k < finding.size(); k++){
                if (out_data[i][j+k] != finding[k]){
                    j += finding.size()-1;
                }
                else if(bit == finding.size()){
                    cout<<"line"<<i<<endl;
                    cout<<j<<"th"<<endl;
                    break;
                }
                else{
                    bit++;
                }
            }
            if (bit){
                break;
            }
            else;
        }
        if (bit){
            break;
        }
        else;
    }   
    return false;
}
//创建编辑
bool easyhtmleditor::creat_files(){ 
    string str;
    int ch2 = 0;
    int ch1 = 0;
    SetPos(0,0);
    pos_x = 0;
    pos_y = 0;
    int num = 0;        
    while (true){    
        ch1 = getch();            
        ch2 = getch();
        string Parr_str;
        switch (ch2){
            case 8:
                cout<<" ";
                if (pos_x){
                    pos_x--; 
                    SetPos(pos_x,pos_y);
                    if (pos_x<=out_data[pos_y].size()&&pos_y<=out_data.size()){
                        Parr_str = out_data[pos_y].substr(pos_x+1);
                        out_data[pos_y].erase(pos_x);
                        out_data[pos_y] += Parr_str; 
                    }
                    else;
                    SetPos(0,pos_y);
                    for (int i = 0; i < 20; i++){
                        cout<<" ";
                    }
                    SetPos(0,pos_y);
                    cout<<out_data[pos_y];
                    SetPos(pos_x,pos_y);
                    }
                else if(pos_x==0){
                    pos_x = out_data[pos_y-1].size();                    
                    out_data[pos_y-1] += out_data[pos_y];
                    out_data[pos_y] = " ";
                    for (int i = pos_y; i < out_data.size()-1; i++){
                        out_data[i] = out_data[i+1];
                    }
                    system("cls");
                    SetPos(0,0);
                    for (int i = 0; i < out_data.size(); i++){
                        cout<<out_data[i]<<endl;
                    }
                    pos_y--;
                    SetPos(pos_x,pos_y);
                    }            
                else;   
                break;
            case 13:
                num = int(pos_y);
                out_data.insert(out_data.begin()+num,"\0");
                system("cls");
                for (int i = 0; i < out_data.size(); i++){
                    cout<<out_data[i]<<endl;
                }
                for (int i = 0; i < 30; i++){
                    cout<<"~"<<endl;
                }
                SetPos(pos_x,pos_y+1);                
                break;
            case 32:
                num = int(pos_x);
                out_data[pos_y].insert(out_data[pos_y].begin()+num,' ');
                SetPos(0,pos_y);
                for (int i = 0; i < 20; i++){
                    cout<<" ";
                }
                SetPos(0,pos_y);
                cout<<out_data[pos_y];
                SetPos(pos_x,pos_y);
                break;
            case 72: 
                if (pos_y){
                    pos_y--;
                }
                else;
                SetPos(pos_x,pos_y);
                break;  
            case 80: 
                pos_y++;
                SetPos(pos_x,pos_y);
                break; 
            case 75: 
                if (pos_x){
                    pos_x--;
                }
                else;                    
                SetPos(pos_x,pos_y);
                break;
            case 77: 
                pos_x++;
                SetPos(pos_x,pos_y);
                break;     
            case 58:
                return true;
            default: 
                string input_str;
                input_str.append(1,ch2);
                if (pos_y>out_data.size()){
                    cout<<ch2;
                    out_data.push_back(input_str);
                }
                else if (pos_y<=out_data.size()&&pos_x==0){
                    cout<<ch2;
                    num = int(pos_y);
                    out_data.insert(out_data.begin()+num,input_str);
                }
                else if (pos_y<=out_data.size()&&pos_x!=0){
                    num = int(pos_x);
                    out_data[pos_y].insert(out_data[pos_y].begin()+num,ch2);
                    SetPos(0,pos_y);
                    for (int i = 0; i < 20; i++){
                        cout<<" ";
                    }
                    SetPos(0,pos_y);
                    cout<<out_data[pos_y];
                    SetPos(pos_x,pos_y);
                }
                else;
                break;
        }
        Sleep(10);  
    }
    return true;
}
//保存
bool easyhtmleditor::save_files(string filename,deque <string> save_Data){
    ofstream in;
    in.open(filename);
    if (in){
       for (int i = 0; i < save_Data.size(); i++){
        in<<save_Data[i]<<"\n";
        }
    }
    else{
        cerr<<"can save the files!!!"<<endl;   
    }
    return true;
}
