#include"../include/exec.h"

using namespace winexec;

bool External_program::open_program(LPCSTR path){
    WinExec(path, SW_SHOWNORMAL);
    if(GetLastError()==740){
        return false;
    }
    else{
        return true;
    }   
}
