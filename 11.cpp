/*
    共享锁 shared_mutex
    c++ 14 共享超时互斥锁shared_timed_mutex
    c++ 17 共享互斥 shared_mutex
    如果只有写时需要互斥，读取时不需要，用普通的锁的话 读取只有一个线程进入，在很多业务场景中，没有充分利用cpu资源

*/
#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include <shared_mutex>
using namespace std;

//c++ 17
//shared_mutex smux;

//c++ 14
shared_timed_mutex stmux;
void ThreadRead(int i){
    for (;;){
        stmux.lock_shared();
        cout << i << "Read" << endl;
        this_thread::sleep_for(500ms);
        stmux.unlock_shared();
        this_thread::sleep_for(1ms);
    }
}
void ThreadWrite(int i){
    for (;;){
        stmux.lock_shared();
       
        stmux.unlock_shared();
        stmux.lock();
        cout << i << "write" << endl;
        this_thread::sleep_for(300ms);
        stmux.unlock();
        this_thread::sleep_for(1ms);
    }
}


int main(){

    for (int i = 0; i < 3;i++){
        thread th(ThreadWrite, i + 1);
        th.detach();
    }
    for (int i = 0; i < 3;i++){
        thread th(ThreadRead, i + 1);
        th.detach();
    }
        getchar();
    return 0;
}