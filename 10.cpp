#include<iostream>
#include<mutex>
#include<thread>
#include<string>
using namespace std;

//超时锁
timed_mutex tmux;

void TestThread(int i ){

    
   
    for (;;){

        if(!tmux.try_lock_for(chrono::milliseconds(500))){
            cout << i << "[try_lock_for timeout]" << endl;
            continue;
        }
        cout << i<<"[in]" << endl;
        this_thread::sleep_for(2000ms);
        tmux.unlock();
        this_thread::sleep_for(1ms);
    }
       
}

//递归锁(可重入) recursive_mutes 和recursive_timed_mutex 用于业务组合 

/*
    同一线程中的同一把锁可以锁多次。避免了一些不必要的死锁
    组合业务 用到用一把锁
*/
recursive_mutex rmux;
//如果已经锁住了就不做判断
void Task1(){
    rmux.lock();
    cout << "task1 [in]" << endl;
    rmux.unlock();
}
void Task2(){
    rmux.lock();
    cout << "task2 [in]" << endl;
    rmux.unlock();

}
void TheadMainRec(int i ){

    for (;;){
        rmux.lock();
        Task1();
        cout << i << "[in]" << endl;
        this_thread::sleep_for(2000ms);
        Task2();
        rmux.unlock();
        this_thread::sleep_for(1ms);
    }
}

int main(){

    // for (int i = 0; i < 3;++i){
    //     thread th(TestThread, i+1);
    //     th.detach();
    // }
    for (int i = 0; i < 3;i++){
        thread th(TheadMainRec, i+1);
        th.detach();
    }

    getchar();
    return 0;
}