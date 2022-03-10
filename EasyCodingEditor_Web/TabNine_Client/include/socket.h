#include<iostream>
#include<string>
#include <winsock2.h>
#include <stdio.h>

#pragma comment ("../lib", "ws2_32.lib")  //加载 ws2_32.dll
#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

namespace socket_server{
class socket_{
    private:

    public:
        SOCKET send_message(SOCKET servSock,string message);
        int close_socket(SOCKET servSock,SOCKET clntSock);
        SOCKET init_server();
        socket_() = default;
        ~socket_() = default;
};
} // namespace socket

