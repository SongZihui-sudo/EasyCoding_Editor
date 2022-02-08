#ifndef _Article_device_h_
#define _Article_device_h_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sys/io.h>
#include <istream>
#include <deque>
#include "estack.h"
#include <cstring>

using namespace std;

static vector <string>                 read_out;
static string                          save_path;
static string                          expand_name;
static string                          expand_State;
static string                          theme_path;
static string                          md_path;
static int                             nums_of_div = 0;
static int                             save_path_state = 0;
static ofstream                        toh;
static fstream                         theme_out;

typedef struct Symbol_table
{
    string name;
    string value;
    Symbol_table *next;
}Symbol_table;

typedef struct strock_int
{
    vector <int> int_arr;
}strock_int;

typedef struct strock_string
{
    vector <string> string_arr;
}strock_string;

static vector <Symbol_table>           table1;
static string                          keyword1 = "#OUTPUTFILE";
static string                          keyword2 = "#THEME";
static string                          keyword3 = "#EXPAND";
static string                          keyword4 = "var";//定义字符串
static string                          keyword5 = "int";//定义数字变量
static string                          keyword6 = "for";
static string                          keyword7 = "static";
static string                          keyword8 = "++";   
static string                          finding;
//栈 存单个变量
static vector <Symbol_table>           Variable_stack;
//栈 存储 字符串或者数字数组
static vector <strock_string>          Variable_stack_string_arr;
static vector <strock_int>             Variable_stack_int_arr;
//按照空格划分语句

vector <string>                 Participle(vector <string> input_file);
deque <string>                  Participle(deque <string> input_file) ;
vector <string>                 Participle(string input_string);

vector <string>                 readout_emakefile();
int                             E_make_lexicalandgrammer_analysis(vector <string> ready_to_make);
static vector <Symbol_table>           table3;
static string                          extension_key = "#EXPAND";        
static fstream                         conf_expan_out;
vector <string>                 read_conf_expend();
vector <string>                 add_new_page(vector <string> save_conffile);
int                             Websocket(vector <string> ws,vector <string> conffile2);
static string                          md_keyword0 = "img";
static string                          md_keyword1 = "#";
static string                          md_keyword2 = ">";
static string                          md_keyword3 = "url";
static string                          md_keyword4 = "___";
static string                          md_keyword5 = "```";
static string                          md_keyword6 = "***";
static string                          md_keyword7 = "---"; 
static string                          md_keyword8 = "::";
static vector                          <Symbol_table> table2;
static vector <int>                    state_machine;
static vector <int>                    end_state_machine;
static vector <string>                 data_share;
static int                             num = 0;
int                             open_mdfile(string FILEPATH);
int                             trans_tohtml(string file_path);
int                             run_task(vector <string> inputarr);
int                             Lexical_analyzer(vector <string> analyer1);
int                             Grammatical_analyer(int State,int number,vector <string> arr,int bit3);
int                             Article_device_run(string filename);

#endif