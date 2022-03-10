#include<iostream>
#include"../include/exec.h"
#include"../include/socket.h"

#pragma comment ("../lib", "ws2_32.lib")  //加载 ws2_32.dll
#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace winexec;
using namespace std;
using namespace socket_server;

winexec::External_program ep;
socket_server::socket_ s;

int main(int argc, char const *argv[]){
    cout<<"Socket Server start successfully!!!"<<endl;
    if(ep.open_program("../bin/TabNine.exe")){
        cout<<"Language start successfully!!!"<<endl; 
        if(s.init_server()){
            while(true){
                s.send_message(s.servSock,"hello");
            }
        }           
        s.close_socket(s.servSock,s.clntSock);
    }
    else{
        cout<<"Language start false!!!"<<endl;
        return -1;
    }
    system("pause");
    return 0;
}
