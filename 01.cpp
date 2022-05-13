#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

void ThreadMain(){
    cout << "begin sub thread: " << this_thread::get_id() << endl;

    cout << "begin thread main" << endl;
    for (int i = 0; i < 10;i++){
        //cout << i << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main(int argc,int *argv[]){

    cout << "begin main thread: " << this_thread::get_id() << endl;

    thread th(ThreadMain);
    //阻塞等待子线程推出
    th.join();
    ///yxx
    return 0;
}