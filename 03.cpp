#include<iostream>
#include<thread>
#include<string>
#include<mutex>
using namespace std;
class Para{
public:
    Para(){
        cout << "para create" << endl; 
    }
    Para(const Para&p){
        cout << "copy para" << endl;
    }
    ~Para(){
        cout << "para drop" << endl;
    }
    string name;
};


void ThreadMain(int p1,float p2,string str,Para p4){
    this_thread::sleep_for(100ms);
    cout << "threadmian: " << p1 << p2 << str <<p4.name<< endl;
}

int main(int argc,int *argv[]){

    cout << "begin main thread: " << this_thread::get_id() << endl;
    thread th;
    {
        float f1 = 12.1f;
        Para p;
        p.name = " test para class";
        //所有的参数都是复制
        th = thread(ThreadMain, 101, f1, " test string",p);
    }
    
    th.join(); 

    return 0;
}