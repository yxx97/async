/*
    scoped_lock用于多个互斥体的免死锁RAII封装器 类似lock
*/
#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<shared_mutex>
using namespace std;
static mutex mux1;
static mutex mux2;
void TestScope1(){
    //模拟死锁 挺100ms等待另一个线程锁mux2
    this_thread::sleep_for(100ms);
    cout << this_thread::get_id() << " begin mux1 lock" << endl;
    //mux1.lock();
    cout << this_thread::get_id() << " begin mux2 lock" << endl;
    //mux2.lock();

    /*
        c++ 11 
        lock同时锁住两个
        但是要解锁
    */
    //lock(mux1, mux2);

    //c++17 scoped_lock
    scoped_lock(mux1, mux2);
    cout << "TestScope1" << endl;
    this_thread::sleep_for(1000ms);
    //mux1.unlock();
    //mux2.unlock();
}

void TestScope2(){

    cout << this_thread::get_id() << " begin mux2 lock" << endl;
    mux2.lock();
    this_thread::sleep_for(500ms);
    cout << this_thread::get_id() << " begin mux1 lock" << endl;
    mux1.lock();
    cout << "TestScope2" << endl;
    this_thread::sleep_for(1000ms);
    mux1.unlock();
    mux2.unlock();
    
}

int main(){

    {
        {
            thread th(TestScope1);
            th.detach();
        }
        {
            thread th(TestScope2);
            th.detach();
        }
    }
    getchar();
    return 0;
}