#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

bool is_exit = false;
void ThreadMain(){
    cout << "begin sub thread: " << this_thread::get_id() << endl;

    cout << "begin thread main" << endl;
    for (int i = 0; i < 10;i++){
        if(is_exit)
            break;
        cout << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main(int argc,int *argv[]){

     cout << "begin main thread: " << this_thread::get_id() << endl;
    
    {
       //thread th(ThreadMain); //出错，thread对象被销毁，子线程还在运行
    }
    // {
    //     thread th(ThreadMain);
    //     th.detach();//子线程与主线程分离 守护线程 不需要管thread 对象了
    //     //坑 主线程退出后 子线程不一定退出  
    // }
    {
        thread th(ThreadMain);
        this_thread::sleep_for(chrono::seconds(3));
        is_exit = true;
        th.join();//主线程阻塞，等待子线程退出
    }
    getchar();

    return 0;
}