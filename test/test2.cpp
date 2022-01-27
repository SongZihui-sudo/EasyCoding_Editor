#include <iostream>

using namespace std;

int test();

int main(){
    string str;
    str = "hello world!!!";
    cout<<str<<endl;
    return 0;
}

int test(string str){
    for(int i = 0;i < str.size()){
        cout<<str[i]<<endl;
    }
    return 0;
}
