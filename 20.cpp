
#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<sstream>
#include<list>
#include<future>
#include<shared_mutex>
using namespace std;

void mythread(){

    this_thread::sleep_for(5s);
    cout << 12 << endl;
}

int main(){

    thread th(mythread);
    //th.detach();
    cout << "end" << endl;
    return 0;
}