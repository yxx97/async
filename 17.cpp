/*
    packaged_task异步调用函数打包
    ackgeed_task包装函数为一个对象,用于异步调用.其返回值能通过std::future对象访问
    与bind的区别,可异步调用,函数访问和获取返回值分开调用

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

string TastPack(int index){

    cout << "begin Test Pack" << index << endl;
    this_thread::sleep_for(2s);
    return "Test Pack return";
}

int main()
{
    packaged_task<string(int)> task(TastPack);
    auto result = task.get_future();
    //同步调用

    //task(100);

    thread th(std::move(task),101);

    cout << "begin result" << endl;
    //测试是否超时
    for (int i = 0; i < 30;++i){
        if(result.wait_for(100ms)!=future_status::ready)
        {
            continue;
        }
            
    }

    if(result.wait_for(100ms)==future_status::timeout){
        cout << "wait result timeout" << endl;
    }else
        cout << "result get:" << result.get() << endl;
    th.join();
    return 0;
}