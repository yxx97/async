/*
    std::atomic
    int  a = 1;简单的复制语句再汇编上也可能是好几条汇编指令
    可以把原子操作理解成一种，不需要用到互斥量加锁(无锁)技术的多线程并发编程方式
    或者可以理解成：原子操作是多线程中不会被打断的程序执行片段；原子比互斥量效率更深一筹
    互斥量的加锁一般针对的是一个代码段(几行代码) 原子操作针对的一般都是一个变量 而不是一个代码段

    //原子操作 一般指 “不可分割的操作” 也就是说这种操作要么是完成的要么是没完成的，不可能出现半完成状态
    std::atomic来代表原子操作，std::atomic是一个类模板. 其实std::atomic是用来封装某一个值的
*/
#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<sstream>
#include<list>
#include<future>
#include<shared_mutex>
using namespace std;

//int g_mycount = 0;//定义一个全局量
std::atomic<int> g_mycount = 0; //封装了一个类型为int 的对象值 就可以当作整形来用

void mythread(){

    for (int i = 0; i < 10000000;++i){
        //g_mycount++;
        //g_mycount += 1;
        g_mycount = g_mycount + 1; //结果不对 不是原子操作
        //一般atomic 针对++，--，+=，&=，|=,^=是支持原子操作的
    }
}


int main(){
    thread th1(mythread);
    thread th2(mythread);
    th1.join();
    th2.join();
    cout <<"两个线程执行完毕，最终的g_mycount的结果是" <<g_mycount << endl;

    return 0;
}