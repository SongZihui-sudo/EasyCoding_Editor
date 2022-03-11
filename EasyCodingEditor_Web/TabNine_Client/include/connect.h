#include<iostream>
#include<string>
#include <stdio.h>
#include<fstream>
#include<vector>

using namespace std;

namespace connect_server{
class connect{
    private:
        string line_buffer;
    public:
        vector <string> read_file(string path);
        int analog_input(vector <string> input);
        connect() = default;
        ~connect() = default;
};
} // namespace socket

