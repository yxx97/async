#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<shared_mutex>
using namespace std;


int main(){

    {
        //共享锁
        static shared_timed_mutex tmux;
        //读取锁 共享锁
        {
            //调用共享锁
            shared_lock<shared_timed_mutex> lock(tmux);
            cout << "read data" << endl;
            //退出栈区 释放共享锁
        }
        //写入锁 互斥锁
        {
            unique_lock<shared_timed_mutex> lock(tmux);
            cout << "write data" << endl;
        }
    }
    return 0;
}