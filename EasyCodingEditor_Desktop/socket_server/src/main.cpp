#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <deque>
#include <string>
#include <iostream>
#include "../include/server.h"
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

using namespace server;
using namespace std;

int main(){
    int send_num = 0;
    int send_times = 0;
    deque <char> File_Buf_Send;
    WSADATA wsaData;
    Electron_server *Es;
    Es = new Electron_server();    
    int port = 2250;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
        cout<<"Failed to load Winsock"<<endl;
        return 1;
    }
    //创建用于监听的套接字
    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port); //1024以上的端口号
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
   
    //cout<<"listening!!!"<<endl;
    int retVal = bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
        if (retVal == SOCKET_ERROR){
            cout<<"Failed bind:"<<WSAGetLastError();
            return 1;
        } 
        if (listen(sockSrv, 10) == SOCKET_ERROR){
            cout<<"Listen failed:"<<WSAGetLastError();
            return 1;
        }
    //等待客户请求到来
    cout<<"waiting client!!!"<<endl;
    while (true){     
        //cout<<"binding!!!"<<endl;
        SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);
        int iSend;
        SOCKET sockConn = accept(sockSrv, (SOCKADDR *)&addrClient, &len);
        if (sockConn == SOCKET_ERROR){
            cout<<"Accept failed:"<<WSAGetLastError()<<endl;
            return 1;
        }
        cout<<"Accept client IP:["<<inet_ntoa(addrClient.sin_addr)<<"]"<<endl;
        char recvBuf_c[10000];
        string recvBuf_cc;
        memset(recvBuf_c, 0, sizeof(recvBuf_c));
        //         //接收数据
        recv(sockConn, recvBuf_c, sizeof(recvBuf_c), 0);
        recvBuf_cc = recvBuf_c;       
        cout<<"sever:"<<recvBuf_cc<<endl;
        File_Buf_Send = Es->judge_recv(recvBuf_cc);
        if (Es->edit_bit){
            send_num++;
            char * Send_buf;
            if (send_num==1){
                //Send_buf = (char*)"1";
                string str_p="1";
                strcpy(Send_buf,str_p.c_str());
                iSend = send(sockConn, Send_buf, sizeof(Send_buf), 0);
                if (iSend == SOCKET_ERROR){
                    cout<<"send failed"<<endl;
                    return 1;
                }
                else{
                    cout<<"msg:"<<Send_buf<<""<<"send successful"<<endl;
                }
            }
            else if((send_num-2)<=File_Buf_Send.size()){
                for (int i = 0; i < File_Buf_Send.size(); i++){
                    //Send_buf = &File_Buf_Send[i];
                    string str_p;
                    str_p.push_back(File_Buf_Send[i]);
                    strcpy(Send_buf,str_p.c_str());
                    iSend = send(sockConn, Send_buf, sizeof(Send_buf), 0);
                    if (iSend == SOCKET_ERROR){
                        cout<<"send failed"<<endl;
                        return 1;
                    }
                    else{
                        cout<<"msg:"<<Send_buf<<""<<"send successful"<<endl;
                    }
                }
            }
            else if ((send_num-2)>File_Buf_Send.size()){
                string str_p = "0";
                strcpy(Send_buf,str_p.c_str());
                 iSend = send(sockConn, Send_buf, sizeof(Send_buf), 0);
                if (iSend == SOCKET_ERROR){
                    cout<<"send failed"<<endl;
                    return 1;
                }
                else{
                    cout<<"msg:"<<Send_buf<<""<<"send successful"<<endl;
                }
             }   
        }
    }
    //free
    Es->~Electron_server();
    system("pause");
    return 0;
}
