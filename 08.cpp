#include<iostream>
#include<mutex>
#include<thread>
#include<string>
using namespace std;
//多线程通信和同步

/*
    初始化(Init): 该线程正在被创建
    就绪(Ready) :该线程在就绪列表中，等待cpu调度
    运行（running)：该线程正在运行
    阻塞(Blocked) : 该线程被阻塞挂起。blocked 状态包括 ：pend(锁，事件，信号量等阻塞)、suspend(主动pend)、delay(延时阻塞)、
                    pendtime(以为锁、事件、信号量事件等超时等待)
    退出(Exit)：该线程运行结束，等待父线程回收其控制资源

    竞争状态(Race Condition)
        多线程同时读写共享数据
    临界区(Critical Section)
        读写共享数据的代码片段
    避免竞争状态策略，对临界区进行保护，同时只能有一个线程进入临界区
*/
static mutex mux;

void TestThread(int i ){

    //获取锁资源，如果没有则阻塞等待
    //mux.lock();//
    for (;;){
        if (!mux.try_lock()) //带来了资源开销，会抑制占用cpu
        {
            cout << "." << flush;
            this_thread::sleep_for(100ms);
            continue;
        }
        cout << "--------" << endl;
        cout << i << endl;
        cout << "+++++++++++" << endl;
        cout << endl;
        mux.unlock();
        this_thread::sleep_for(1000ms);
    }
       
}

int main(){

    for (int i = 0; i < 10;++i){
        thread th(TestThread, i);
        th.detach();
    }
    getchar();
    return 0;
}