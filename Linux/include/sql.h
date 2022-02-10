#ifndef sql_h_
#define sql_h_

#include <deque>
#include <string>
#include <iostream>

using namespace std;

deque <string> select(const char * database,const char *table);

#endif