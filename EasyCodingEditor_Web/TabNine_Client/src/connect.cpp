#include"../include/connect.h"

vector <string> connect_server::connect::read_file(string path){
    string file_data;
    vector<string> file_buffer;
    fstream out;
    out.open(path);
    if(out){
        while (getline(out,file_data)){
            cout<<file_data<<endl;
            file_buffer.push_back(file_data);
        };
    }
    else{
        cout<<"Couldn't open"<<endl;
        return {""};
    }
    return file_buffer;
}

int connect_server::connect::analog_input(vector<string> input){
    return 0;
}
