//call_once 多线程调用函数，当函数只进入一次
#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
void SystemIiit()
{
    cout << "Call SystemIiit" << endl;
}

void SystemIiitOne(){
    static std::once_flag flag;
    std::call_once(flag, SystemIiit);
}

int main(){
    SystemIiitOne();
    SystemIiitOne();
    SystemIiitOne();
    for (int i = 0; i < 3;i++){
        thread th(SystemIiitOne);
        th.detach();
    }
    getchar();
    return 0;
}