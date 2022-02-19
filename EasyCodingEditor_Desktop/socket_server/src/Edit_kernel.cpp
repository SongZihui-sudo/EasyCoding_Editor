#include "../include/server.h"

using namespace server;

int Electron_server::Edit_kernel(string edit_str){
    int ch2 = 0;
    if (edit_str == "edit"){
        edit_bit = 1;
        return 1;
    }
    else if(edit_str == "end"){
        edit_bit = 0;
        return 1;
    }
    else if(edit_str[0] == 'x'){
        edit_str.erase(edit_str.begin());
        if (pos_x){
            pos_x = atoi(edit_str.c_str()); 
        }
        else{
            return 1;
        }
    }
    else if(edit_str[0] == 'y'){
        edit_str.erase(edit_str.begin());
        if (pos_y){        
            pos_y = atoi(edit_str.c_str());
        }
        else{
            return 1;
        }
    }
    else{
        ch2 = atoi(edit_str.c_str());
    }
    switch (ch2){
    case 13:insert_char('\n');break;
    case 8:backspacce();break;
    case 9:insert_char(' ');insert_char(' ');insert_char(' ');insert_char(' ');break;
    case 33:break;
    case 34:break;
    case 32:insert_char(' ');break;
    default:insert_char(ch2);break;
    }
    return 0;
}

int Electron_server::insert_char(char insert_char){
    if (pos_x<=File_Buf.size()){
        File_Buf.insert(File_Buf.begin()+pos_x,insert_char);
    }
    else{
        File_Buf.push_back(insert_char);
    }
    return 0;
}

int Electron_server::backspacce(){
    deque <char> P_File_buf;
    if (pos_x<File_Buf.size()){
        for (int i = 0; i < 1; i++){
		    char temp = File_Buf[0];
		    for (int j = 0; j <File_Buf.size(); j++){
			    File_Buf[j] = File_Buf[j + 1];
		    }
		    File_Buf[File_Buf.size()] = temp;
	    }
    }
    else{
        File_Buf.pop_back();
    }
    return 0;
}