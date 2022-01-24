#include <iostream>
#include "../include/easyhtmleditor.h"
#include <Windows.h>

using namespace edt;
using namespace std;

void SetSize(unsigned uCol,unsigned uLine);

int main(){
    system("title EasyCodingEditor");
    unsigned x = 500;
    unsigned y = 500;
    SetSize(x,y);
    edt::easyhtmleditor e;
    //初始化字符集
    int k = 0;
    for (int i = 0; i < 60; i++){
        cout<<"~"<<endl;
    }
    for (int i = 0; i < e.word.size()-1; i++){
        for (int j = 0; j < e.word.size()-i-1; j++){
            if (e.word[j] > e.word[j+1]){
                k = e.word[j];
                e.word[j] = e.word[j+1];
                e.word[j+1] = k;
            }   
        }
    }
    e.commander();
    system("pause");
    return 0;
}

//设置窗口大小
void SetSize(unsigned uCol,unsigned uLine){
    char cmd[64];
    sprintf(cmd,"mode con cols=%d lines=%d",uCol,uLine);
    system(cmd);
}
