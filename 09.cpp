#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<deque>
using namespace std;

static mutex mux;
//mutex 的坑
void TestThread(int i ){

    
   
    for (;;){

        mux.lock();
        cout << i<<"[in]" << endl;
        this_thread::sleep_for(1000ms);
        mux.unlock();
        this_thread::sleep_for(1ms);
    }
       
}

int main(){

    for (int i = 0; i < 3;++i){
        thread th(TestThread, i);
        th.detach();
    }
    getchar();
    return 0;
}
deque<char> q;
uint32_t pre = 0;
const int a = 20000;
void saveMsg(char *msg,uint32_t len, uint32_t ts)
{
    if(ts>pre){
        int cap = 20000 - q.size();
        if(len>cap){
            int x = q.size() + len - a;
            for (int i = 0; i < x;++i){
                q.pop_front();
            }
            for (int i = 0; i < len;++i){
                q.push_back(msg[i]);
            }
        }
        else{
            for (int i = 0; i < len;++i){
                q.push_back(msg[i]);
            }
        }
        pre = ts;
    }
    else{
        
    }


}