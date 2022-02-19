#include "../include/server.h"

using namespace std;
using namespace server;

Electron_server::Electron_server(){
    //初始化函数指针数组
    fun_arr[0] = &connect;
    fun_arr[1] = &Edit_kernel;
    fun_arr[2] = &close;
    fun_arr[3] = &Edit_kernel;
}
Electron_server::~Electron_server(){
    free(fun_arr);
}
deque <char> Electron_server::judge_recv(string recv){
    //(this->*fun_arr[0])(recv);
    for (int i = 0; i < sizeof(cmd)/sizeof(cmd[0]); i++){
        if (recv == cmd[i]){
            (this->*fun_arr[i])(recv);
            break;
        }
        else{
            continue;
        }        
    }
    if (edit_bit){
        (this->*fun_arr[1])(recv);
    }
    return File_Buf;
}

int Electron_server::close(string close_msg){
    cout<<"断开连接！！！服务端下线了！！！"<<endl;;
    exit(1);
    return 1;
}

int Electron_server::connect(string msg){
    cout<<"连接服务端成功！！！"<<endl;;
    return 0;
}