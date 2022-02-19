#ifndef socket_h
#define socket_h

#include <iostream>
#include <deque>
#include <stack>
#include <string>
#include <WinSock2.h>

using namespace std;

namespace server{

class Electron_server{//建立映射关系，直接调用函数
    public:
        int             (Electron_server::*fun_arr[100])(string);
        deque <char>    File_Buf;
    public:
        int             edit_bit = 0;
        int             pos_x = 0;
        int             pos_y = 0;
        int             page_now = 0;
        int             page = 0;
    public:
        deque <char>    judge_recv(string recv);
                        Electron_server();
                        ~Electron_server();
        int             close(string close_msg);
        int             connect(string msg);            
        int             Edit_kernel(string edit_str);
        int             space();
        int             backspacce();
        int             enter();
        int             page_up();
        int             page_down();
        int             Tab();
        int             insert_char(char insert_char);
    private:
        string          cmd[4] = {"connect","edit","close","end"};
    };
}
#endif