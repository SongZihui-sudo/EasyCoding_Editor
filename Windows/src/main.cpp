#include <iostream>
#include "../include/EasyCodingEditor.h"
#include <Windows.h>
#include "../include/Code_highlighting.h"
#include "../include/Code_completion.h"
#include "../include/wke.h"

using namespace edt;
using namespace std;
using namespace cht;
using namespace cct;

void SetSize(unsigned uCol,unsigned uLine);

int main(){
    wstring strWkeFilePath = L"EasycodingEditor";
    wkeSetWkeDllPath(strWkeFilePath.c_str());
    wkeInitialize();
    SetConsoleOutputCP(65001);
    system("title EasyCodingEditor");
    unsigned x = 150;
    unsigned y = 40;
    SetSize(x,y);
    edt::easyhtmleditor e;
    cct::Code_completion c2;
    //初始化字符集
    int k = 0;
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
