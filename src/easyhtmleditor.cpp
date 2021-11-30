#include <iostream>
#include <fstream>
#include <vector>
#include "easyhtmleditor.h"
#include <bits/stdc++.h> 
#include <fstream>

using namespace std;

int main(){
    vector <string> nothing;
    printf(" \033[41;36m EASYHTMLEDITOR \033[0m");
    cout<<endl;
    frame *p;
    p = new(frame);
    p->shell(nothing);
    return 0;
}

int frame::shell(vector <string> o_line){
    while (true){
        cout<<":";
        string c;
        string f;
        cin>>c;
        if (c == "/"){
            string find_s;
            cin>>find_s;
            for (int i = 0,j = 1 ; j < c.size(); i++,j++){
                find_s[i] = c[j];
            }
            frame::find(find_s);
        }
        else if(c == "i" ){
            frame::input(0);
        }
        else if(c == "wq" ){
            cin>>f;
            frame::write(o_line,f);
            break;
        }
        else if ( c == "o"){
            cin>>f;
            frame::read(f);
            break;
        }
        
        else;
    }
    return 0;
}

/*
123456
345
*/
int frame::find(string find_Str){
    long long bit_equal = 0;
    int k = 0;
    for (int i = 1; i < buf.size() ; i++){
        for (int j = 0;  j < buf[i].size() ; j++){
            if ( buf[i][j] != find_Str[k] ){
                bit_equal = 0;
                j+=find_Str.size() - 1;    
            }
            else if(bit_equal == find_Str.size()){
                break;
            }
            else{
                bit_equal++;
                k++;
            }
        }
        if (bit_equal){
            cout<<buf[i]<<endl;
            break;
        }   
    }
    return 0;
}

int frame::write(vector <string> print_to_file,string file_name){
    ofstream fout;
    file_name = string("../file/") + file_name;
    fout.open(file_name);
    if (fout){
        for (int i = 0; i < print_to_file.size(); i++){
            fout<<print_to_file[i]<<endl;
        }
        frame::line.clear();
        frame::parr.clear();
        buf.clear();
        exit(0);
    }
    else{
        cout<<"CAN NOT SAVE THE FILE!"<<endl;
        return -1;
    }
    return 0;
}

int frame::read(string read_Str){
    long long lines_number = 0;
    ifstream fin;
    read_Str=string("../file/") + read_Str;
    fin.open(read_Str);
    if(fin){
        while(getline(fin,read_Str)){
            frame::line.push_back(read_Str);
            read_Str = string("line") + to_string(lines_number) + string(":") + read_Str;
            buf.push_back(read_Str);
            lines_number++;
        }
        for (int i = 0; i < buf.size(); i++){
            cout<<buf[i]<<endl;
        }
        frame::input(lines_number);
    }
    else{
        cout<<"CAN NOT OPEN THE FILE!"<<endl;
        return -1;
    }
    return 0;
}

int frame::input(long long lines){
    kennel *k;
    k = new(kennel);
    while (true){            
        string line_input;
        cout<<"line"<<lines<<":";  
        getline(cin,line_input);
        if ( line_input == "e"){
            frame::shell(frame::line);
        }
        else if( line_input == "w"){  
            cout<<"page up";          
            lines--;
            k->split_line_function();
            cout<<"\n";
            int last = buf.size();
            frame::parr.push_back(buf[last - 1]);
            convert_parr.push_back(convert[convert.size() - 1]);
            buf.pop_back();
            for ( int i = 0; i < buf.size(); i++){
                cout<<buf[i]<<endl;
            }
            cout<<"line"<<lines<<":";  
        }
        else if ( line_input == "s"){
            cout<<"page down";
            k->split_line_function();
            cout<<"\n";
            buf.push_back(parr[parr.size()-1]);
            parr.pop_back();
            for (int i = 0; i < buf.size(); i++){
                cout<<buf[i]<<endl;
            }
            k->split_line_function();
            cout<<"\n";
        }
        else if ( line_input == "d" ){   
            cout<<"delete last";         
            lines-=2;
            k->split_line_function();
            cout<<"\n";
            buf.pop_back();
            for (int i = 0; i < buf.size(); i++){
                cout<<buf[i]<<endl;
            }
            k->split_line_function();
            cout<<"line"<<lines<<":";  
        }
        else if ( line_input == "a"){
            cout<<"view all";
            k->split_line_function();
            cout<<"\n";
            for (int i = 0; i < buf.size(); i++){
                cout<<buf[i]<<endl;
            }
            k->split_line_function();
        }
        else{
            string line_number = string("line") + to_string(lines) + string(":") + line_input;
            buf.push_back(line_number);
            frame::line.push_back(line_input);
            k->Gramma_analysis(line_input);
            cout<<"\n";
            lines++;
        }
    }
    return 0;
}
int kennel::Gramma_analysis(string Line__){
    int bit_title = 0;
    for( int i = 0; i < Line__.size();i++ ){
        if ( Line__[i] == kennel::title[0] ){
            bit_title = 1;    
        }
        else if(Line__[i] == ' '){
            break;
        }
        else{
            bit_title = 0;
            break;
        }
    }
    int bit_url = 0;
    for (int i = 0 ; i < kennel::url.size();i++) {
        if (Line__[i] == kennel::url[i]){
            bit_url = 1;        
        }
        else{
            bit_url = 0;
            break;
        }
    }
    int bit_img = 0;
    for(int i = 0; i < kennel::img.size(); i++ ){
        if ( Line__[i] == kennel::img[i] ){
            bit_img = 1;
        }
        else{
            bit_img = 0;
            break;
        }
    } 
    int bit_code_begin = 0;
    for (int i = 0; i < kennel::code_begin.size(); i++){
        if (Line__[i] == kennel::code_begin[i] ){
            bit_code_begin = 1;
        }
        else{
            bit_code_begin = 0;
            break;
        }
    }
    int bit_code_end = 0;
    for (int i = 0; i < kennel::code_end.size(); i++){
        if (Line__[i] == kennel::code_end[i] ){
            bit_code_end = 1;
        }
        else{
            bit_code_end = 0;
            break;
        }
    }
    int bit_sqite_line = 0;
    for (int i = 0; i < kennel::split_line.size(); i++){
        if (Line__[i] == kennel::split_line[i]){
            bit_sqite_line = 1;
        }
        else{
            bit_sqite_line = 0;
            break;
        }    
    }
    if (bit_title){
        kennel::Title_function(Line__);   
    }
    else if (bit_url){
        kennel::url_function(Line__);
    }
    else if (bit_img){
        kennel::img_function();
    }
    else if (bit_code_begin){
        kennel::code_begin_funcition();
    }
    else if (bit_code_end){
        kennel::code_end_function();
    }
    else if (bit_sqite_line){
        kennel::split_line_function();
    }
    else{
        convert.push_back(space_string + Line__);
        kennel::print_convert();
    }
    return 0;
}

int kennel::Title_function(string Tiltle_name){
    long long numsoft;
    cout<<"\n";
    for (int i = 0; i < Tiltle_name.size(); i++){
        if (Tiltle_name[i] == ' '){
            numsoft = i;
            break;
        }
    }
    for (int i = 0; i < 20; i++){
        space.push_back(' ');
    }
    convert.push_back(string("Level")+
    to_string(numsoft)+string("heading") + space_string + Tiltle_name);
    kennel::print_convert();
    return 0;
}

int kennel::url_function(string url_things){
    int numsofspace = 0;
    long long numsoft;
    for (int i = 0; i < url_things.size(); i++){
        if ( url_things[i] == ' ' ){
            numsofspace++;
        } 
        else if ( numsofspace == 2){
            numsoft = i;
            break;
        }
        else{
            continue;
        }   
    }
    string url_name;
    for (int i = numsoft; i < url_things.size(); i++){
        url_name[i] = url_things[i];
    }
    convert.push_back(space_string + url_name);
    kennel::print_convert();
    return 0;
}

int kennel::split_line_function(){
    vector <char> _arr;
    const int numsof_ = 50;
    for (int i = 0; i < numsof_; i++){
        _arr.push_back('_');
    }
    string __string( _arr.begin(), _arr.end());
    convert.push_back( space_string + __string);
    kennel::print_convert();
    return 0;
}

int kennel::img_function(){
    for (int i = 0; i < 20; i++){
    }
    convert.push_back(space_string + string("img"));
    kennel::print_convert();
    return 0;
}

int kennel::code_begin_funcition(){
    return 0;
}

int kennel::code_end_function(){
    return 0;
}

int kennel::print_convert(){
    for (int i = 0; i < convert.size(); i++){
        cout<<convert[i]<<endl;
    }
    return 0;
}