#include<iostream>
#include"../include/exec.h"
#include"../include/connect.h"

using namespace winexec;
using namespace std;
using namespace connect_server;

winexec::External_program ep;
connect_server::connect c;

int main(int argc, char const *argv[]){
	if(ep.open_program("../bin/TabNine.exe")){
		cout<<"Start language Server Success!!!"<<endl;
		c.analog_input(c.read_file("../Temporary_Files/cur.out"));
	}
	else{
		cout<<"Starting language server false!!!"<<endl;
		return -1;
	}
	return 0;
}
