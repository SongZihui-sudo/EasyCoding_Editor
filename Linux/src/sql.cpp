#include "../include/sql.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

deque <string> select(const char * database,const char *table){
    deque <string> file_data;
    //查询所有数据 
    sqlite3 *db; 
    sqlite3_stmt * stmt = NULL; 
    const char *zTail;
    string line;
    string parr_table = string("SELECT KEY_WORDS FROM ") + string(table) + string(";");
    int r =sqlite3_open(database,&db) ;//打开数据库 
    if (sqlite3_prepare_v2(db, parr_table.c_str() , -1, &stmt, &zTail) ==SQLITE_OK){       
        while( sqlite3_step(stmt) ==SQLITE_ROW ) { 
                const unsigned char * name = sqlite3_column_text( stmt,0); 
                //进行类型转换
                const char* p = (const char*)(char*)name;
                line = p;
                file_data.push_back(line);
                //printf("%s/n",name); 
        } 
    }
    else
    {
        printf("EC:OPEN DATABASE FILED!!!\n");
        exit(1);
    }
    sqlite3_finalize(stmt); 
    //关闭数据库 
    sqlite3_close(db); 
    return file_data;
}