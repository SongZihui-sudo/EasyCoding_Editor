#include <iostream>
#include "../include/easyhtmleditor.h"

using namespace edt;
using namespace std;

int main(){
    edt::easyhtmleditor e;
    //初始化字符集
    int k = 0;
    for (int i = 0; i < 100; i++){
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