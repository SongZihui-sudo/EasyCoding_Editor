#include "../include/EasyCodingEditor.h"
#include "../include/Code_highlighting.h"
#include "../include/Code_completion.h"
#include "../include/Markdown_parser.h"
#include <termio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include "../include/key_code.h"

using namespace edt;
using namespace std;
using namespace cht;
using namespace cct;
using namespace mpt;

#define  KEY_EVENT_DEV1_NAME    "/dev/input/event2"

cht::Code_highlighting C3;
cct::Code_completion cc2;
mpt::Markdown_parser mp2; 
 
int easyhtmleditor::Edit_kernal(){
    int bit_capslock = 0;
    CLEAR();
	if (!out_data.empty());
    else{
        deque <string> write_page;
        write_page.push_back("");
        page_arr.push_back(write_page);
    }        
    string        str;
    int 		  ch1 = 0;
    int 		  ch2 = 0;
    SetPos(0,0);
    int 		  num = 0;  
    string        Parr_str;

    int           l_ret = -1;
	int           i = 0;
	
	int           key_fd  = 0;
	
	int           enter_num = 0;
	struct input_event key_event  = {0};
	
	key_fd = open(KEY_EVENT_DEV1_NAME, O_RDONLY);
	if(key_fd <= 0)
	{
	    printf("---open /dev/input/event1 device error!---\n");
	    return l_ret;
	}
	
	while(1)
	{
	    
		l_ret = lseek(key_fd, 0, SEEK_SET);
		l_ret = read(key_fd, &key_event, sizeof(key_event));
		
		if(l_ret)
		{		            
			if(key_event.type == EV_KEY&& (key_event.value == 0 || key_event.value == 1)){	
            //C3.resetFColor();
			//printf("key %d\n",key_event.code);
			switch (key_event.code){		    
            case KEY_BACKSPACE:
                if (cc2.c_str.empty());
                else{
                        cc2.c_str.pop_back();
                    }
                if (last_str.empty());
                else{                                           
                    last_str.pop_back();
                    }
                if (pos_x){                        
                    num = pos_x;
                    pos_x--;   
                    last_x--;                      
                    SetPos(pos_x,pos_y -  (page_now-1)*page_y);
                    if (num<page_arr[page_now-1][pos_y -  (page_now-1)*page_y].size()&&pos_y- (page_now-1)*page_y<=page_arr[page_now-1].size()){
                        Parr_str =page_arr[page_now-1][pos_y -  (page_now-1)*page_y].substr(num);
                        page_arr[page_now-1][pos_y -  (page_now-1)*page_y].erase(pos_x);
                        page_arr[page_now-1][pos_y -  (page_now-1)*page_y] += Parr_str; 
                    }
                    else if(num==page_arr[page_now-1][pos_y -  (page_now-1)*page_y].size()&&pos_y- (page_now-1)*page_y<=page_arr[page_now-1].size()){
                        Parr_str = page_arr[page_now-1][pos_y-(page_now-1)*page_y][page_arr[page_now-1][pos_y-(page_now-1)*page_y].length()-1];
                        page_arr[page_now-1][pos_y -  (page_now-1)*page_y].pop_back();
                    }
                    else;
                    SetPos(0,pos_y -  (page_now-1)*page_y);
                    for (int i = 0; i < 100; i++){
                        cout<<" ";
                    }
                    SetPos(0,pos_y -  (page_now-1)*page_y);
                    cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y];
                    }
                else if(pos_x == 0 && pos_y -  (page_now-1)*page_y == 0){
                    pos_x = 0;
                    last_x = 0;
                    pos_y = (page_now-1)*page_y;
                }
                else if(pos_x==0){
                    pos_x = page_arr[page_now-1][pos_y-1 -  (page_now-1)*page_y].size();//  out_data[pos_y-1].size();                    
                    page_arr[page_now-1][pos_y-1 -  (page_now-1)*page_y] += page_arr[page_now-1][pos_y -  (page_now-1)*page_y]; //out_data[pos_y];
                    page_arr[page_now-1].erase(page_arr[page_now-1].begin()+pos_y -  (page_now-1)*page_y);
                    if (page_arr[page_now-1].size() < page_y&&exact_buffer.size()!=0){
                        page_arr[page_now-1].push_back(exact_buffer.top());
                        exact_buffer.pop();
                    }    
                    last_str = "";
                    CLEAR();
                    for (int i = 0; i < page_arr[page_now-1].size(); i++){
                        cout<<page_arr[page_now-1][i]<<endl;
                    }
                    pos_y--;
                }      
                else;   
                C3.Lexical_analysis(page_arr[page_now-1]);                                
                    SetPos(pos_x,pos_y -  (page_now-1)*page_y);
                    break;
                	//回车
                    case KEY_ENTER:     
                        enter_num++;
                        if (enter_num==1){
                            break;
                        }                 
                        last_str = "";                   
                	    num = int(pos_y) -  (page_now-1)*page_y;
                	    if (pos_x>=page_arr[page_now-1][pos_y -  (page_now-1)*page_y].size()){
                    	    page_arr[page_now-1].insert(page_arr[page_now-1].begin()+num+1,""); 
                	    }         
                	    else{
                    	    str = page_arr[page_now-1][pos_y -  (page_now-1)*page_y].substr(pos_x);
                    	    page_arr[page_now-1][pos_y -  (page_now-1)*page_y].erase(pos_x);
                    	    page_arr[page_now-1].insert(page_arr[page_now-1].begin()+num+1,str);
                        }
                	    if (page_arr[page_now-1].size() > page_y){
                    	    exact_buffer.push(page_arr[page_now-1][page_arr[page_now-1].size()-1]);
                    	    page_arr[page_now-1].pop_back();
                	    }       
                	    CLEAR();
                        for (int i = 0; i < page_arr[page_now-1].size(); i++){
                            cout<<page_arr[page_now-1][i]<<endl;
                        }                    
                	    C3.Lexical_analysis(page_arr[page_now-1]);                                
                	    pos_x = 0;
                	    last_x = 0;                    
                	    pos_y++;
                	    if (pos_y>=page_y*(page_now)){
                    	    pos_y--;
                    	    break;
                	    }
                	    else{
                    	    SetPos(pos_x,pos_y-(page_now-1)*page_y);    
                        }
                	    break;
                    //TAB
                case KEY_TAB:
                    if (cc2.c_str.empty());
                    else{
                        cc2.c_str.clear();
                        cc2.c_str = "";
                        last_x = 0;
                        last_str.push_back(' ');
                        last_str.push_back(' ');
                        last_str.push_back(' ');
                        last_str.push_back(' ');
                    }
                    if (pos_x){                    
                        num = pos_x;                    
                    }
                    else{
                        num = 0;
                    }
                    pos_x +=4;
                    page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num+1,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num+2,' ');
                    page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num+3,' ');
                    SetPos(0,pos_y -  (page_now-1)*page_y);
                    for (int i = 0; i < 30; i++){
                        cout<<" ";
                    }
                    SetPos(0,pos_y -  (page_now-1)*page_y);
                    cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y];
                    C3.Lexical_analysis(page_arr[page_now-1]);                                
                    SetPos(pos_x,pos_y -  (page_now-1)*page_y);                    
                    break;
                //空格
                case KEY_SPACE:
                    if (cc2.c_str.empty());
                    else{
                        cc2.c_str.clear();
                        cc2.c_str = "";
                        last_x = 0;
                        last_str.push_back(' ');
                    }
                    if (pos_x){                    
                        num = pos_x;                    
                    }
                    else{
                        num = 0;
                    }
                    pos_x++;
                    page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num,' ');    
                    SetPos(0,pos_y -  (page_now-1)*page_y);
                    for (int i = 0; i < 30; i++){
                        cout<<" ";
                    }
                        SetPos(0,pos_y -  (page_now-1)*page_y);
                        cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y];
                        C3.Lexical_analysis(page_arr[page_now-1]);                                
                        SetPos(pos_x,pos_y -  (page_now-1)*page_y);
                        break;
                    case KEY_PAGEUP:
                        if (page_now==1){
                            page_now = page_now;
                        }
                        else{
                            page_now--;
                            pos_y= pos_y - page_y;
                        }
                        CLEAR();
                        for (int i = 0; i < page_arr[page_now-1].size(); i++){
                            cout<<page_arr[page_now-1][i]<<endl;
                        }
                        C3.Lexical_analysis(page_arr[page_now-1]);     
                        SetPos(page_x-20,page_y);
                        cout<<"page_y"<<page_now;                   
                        SetPos(0,0);
                        if (exact_buffer.size()){
                            for (int i = 0; i < exact_buffer.size(); i++){
                                exact_buffer.pop();
                            }
                        }
                        else;
                        break;
                    case KEY_PAGEDOWN:
                        if (page_now<=page_y&&page_y){ 
                            page_now++;
                            pos_y+=page_y;           
                        }
                        else{
                            deque <string> space_line;
                            space_line.push_back("");
                            page_now++;
                            page_y++;
                            pos_y+=page_y;
                            page_arr.push_back(space_line);
                            pos_x = 0;
                        }
                        CLEAR();
                        for (int i = 0; i < page_arr[page_now-1].size(); i++){
                            cout<<page_arr[page_now-1][i]<<endl;
                        }
                        C3.Lexical_analysis(page_arr[page_now-1]);  
                        SetPos(page_x-20,page_y);
                        cout<<"page_y"<<page_now;
                        SetPos(0,0);
                        if (exact_buffer.size()){
                            for (int i = 0; i < exact_buffer.size(); i++){
                                exact_buffer.pop();
                            }   
                        }
                        break;
                    //上
                    case KEY_UP:
                        if (pos_y <= (page_now-1)*page_y){
                            pos_y = pos_y;
                            break;
                        }
                        else{
                            if (pos_y){
                                pos_y--;
                            }
                            else;
                        }
                        SetPos(page_x-10,page_y);
                        cout<<"Line:"<<pos_y; 
                        pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y].size();
                        last_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y].size();
                        SetPos(pos_x,pos_y -  (page_now-1)*page_y);
                        //MOVEUP(1);
                        break;   
                    //下
                    case KEY_DOWN:
                        pos_x = pos_x-4;
                        if (pos_y-  (page_now-1)*page_y>=page_arr[page_now-1].size()-1);
                        else pos_y++;
                        SetPos(page_x-10,page_y);
                        cout<<"Line:"<<pos_y; 
                        pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y].size();
                        SetPos(pos_x,pos_y -  (page_now-1)*page_y);
                        //MOVEDOWN(1);
                        break; 
                    //左
                    case KEY_LEFT: 
                        pos_x = pos_x-4;
                        if (pos_x){
                            pos_x--;
                            last_x--;
                        }
                        else; 
                        SetPos(page_x-30,page_y);
                        cout<<pos_x<<"th";                
                        SetPos(pos_x,pos_y -  (page_now-1)*page_y);
                        //MOVELEFT(1);
                        break;
                    //右
                    case KEY_RIGHT:
                        if (pos_x>=page_arr[page_now-1][pos_y-  (page_now-1)*page_y].size()) pos_x = page_arr[page_now-1][pos_y-  (page_now-1)*page_y].size();
                        else{
                            pos_x++;
                            last_x++;                    
                        } 
                        SetPos(page_x-30,page_y);
                        cout<<pos_x<<"th"; 
                        SetPos(pos_x,pos_y -  (page_now-1)*page_y);
                        //MOVERIGHT(1);
                        break;     
                    //esc
                    case KEY_ESC:
                        return true;
                    case KEY_CAPSLOCK:
                        bit_capslock++;
                        break;
                    default:       
                        int bit = 0;
                        string input_str;
                        int mid = 0;
                        int left = word[0];
                        int right = word[word.size()-1];                            
                        for (int i = 0; i < word.size(); i++){
                            mid = (left+right)/2;
                            if (ch2>mid){
                                left = mid + 1;                            
                            }
                            else if(ch2<mid){
                                right = mid -1;
                            }
                            else{
                                bit =1; 
                                SetPos(pos_x,pos_y -  (page_now-1)*page_y);                             
                                cout<<ch2;                            
                                pos_x++;
                                last_x++;
                                break;
                            }
                        }
                        if (bit){
                            if (pos_x==1&&pos_y-  (page_now-1)*page_y>page_arr[page_now-1].size()){
                                input_str.push_back(key_event.value);
                                page_arr[page_now-1] .push_back(input_str);
                                input_str.clear();
                            }
                            else if(pos_x==1&&pos_y -  (page_now-1)*page_y<=page_arr[page_now-1].size()){
                                page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin(),key_event.value);
                                SetPos(0,pos_y -  (page_now-1)*page_y);
                                cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y];
                            }                 
                            else if(pos_y-  (page_now-1)*page_y<=page_arr[page_now-1].size()&&pos_x<=page_arr[page_now-1][pos_y -  (page_now-1)*page_y].size()){
                                num = int(pos_x);
                                page_arr[page_now-1][pos_y -  (page_now-1)*page_y].insert(page_arr[page_now-1][pos_y -  (page_now-1)*page_y].begin()+num-1,key_event.value);
                                for (int i = 0; i < 100; i++){
                                    cout<<" ";
                                }
                                SetPos(0,pos_y -  (page_now-1)*page_y);
                                cout<<page_arr[page_now-1][pos_y -  (page_now-1)*page_y];
                            }
                            else if(pos_x > page_arr[page_now-1][pos_y -  (page_now-1)*page_y].size()&&pos_y -  (page_now-1)*page_y<=page_arr[page_now-1].size()){
                                page_arr[page_now-1][pos_y -  (page_now-1)*page_y].push_back(key_event.value);
                            }
                            else;      
                            string code_compl = cc2.Lexical_analysis(ch2,pos_y -  (page_now-1)*page_y,last_x);
                            if (last_x-1  <= cc2.c_str.size()){   
                                if (code_compl[code_compl.length()-1]!=key_event.value){
                                    SetPos(0,pos_y - (page_now-1)*page_y);   
                                    for (int i = 0; i < 100; i++){
                                        cout<<" ";
                                    }                                  
                                    page_arr[page_now-1][pos_y - (page_now-1)*page_y].clear();
                                    last_str+=code_compl;                            
                                    page_arr[page_now-1][pos_y - (page_now-1)*page_y] = last_str ;
                                    SetPos(0 ,pos_y - (page_now-1)*page_y);    
                                    cout<<page_arr[page_now-1][pos_y - (page_now-1)*page_y];
                                    C3.Lexical_analysis(page_arr[page_now-1]); 
                                    pos_x = page_arr[page_now-1][pos_y - (page_now-1)*page_y].size(); 
                                    SetPos(pos_x,pos_y -  (page_now-1)*page_y);                              
                                    break;
                                }
                                else;
                            }        
                            else;                        
                            C3.Lexical_analysis(page_arr[page_now-1]);                                
                            SetPos(pos_x,pos_y -  (page_now-1)*page_y);
                        }
                        else;   
                        break;
			    }
		    }
        }
	}
	close(key_fd);
	return 0;
}