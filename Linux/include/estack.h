#ifndef _estack_hpp
#define _estack_hpp

#include <iostream>
#include <string>

using namespace std;

#include<iostream>
#include<stdlib.h>

using namespace std;

#define MAXSIZE 0xffff

template<class type>
class estack
{
public:
    
    int top;
    type* data;
    int maxsize;
    type* start;
    type* finish;

public:
    estack():top(-1),maxsize(MAXSIZE){
        data=new type[maxsize];
        if(data==NULL)
        {
            cerr<<"ERROR!"<<endl;
            exit(1);
        }
    }
    estack(int size):top(-1),maxsize(size)
    {
        data=new type[maxsize];
        if(data==NULL)
        {
            cerr<<"ERROR!"<<endl;
            exit(1);
        }
    }
    ~estack()
    {
        //delete[] data;
    }
    //是否为空
    bool Empty();
    //压栈
    int Push(type tp);
    //出栈
    void Pop();
    //栈大小
    int Size();
    //第一个元素的指针
    type* begin(){
        if (top == -1){
            cout<<"empty"<<endl;
        }
        else{
            start = data;
            return start;
        }
    }
    //最后一个元素的指针
    type* end(){
        if (top == -1){
            cerr<<"ERROR!!!\n";
        }
        else{
            finish = data[Size()];
        }
        return finish;
    };
};

template<class type>
bool estack<type>::Empty()
{
    if(top==-1){
        return true;
    }
    else
        return false;
}

template<class type>
int estack<type>::Push(type tp)
{
    if(top+1<maxsize){
        if (tp == "")
        {
            return 1;   
        }
        else
            data[++top]=tp;
    }
    else
    {
        cout<<"full!!!\n";
        exit(1);
    }
    return 0;
}

template<class type>
void estack<type>::Pop()
{
    if(top>=0)
    {
        top--;
    }
    else
    {
        cout<<"empty!!!\n";
        exit(1);
    }
}

template<class type>
int estack<type>::Size()
{
    return top+1;
}

#endif