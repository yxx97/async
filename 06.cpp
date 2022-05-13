#include<iostream>
#include<thread>
#include<string>
//学习使用lamada表达式进行线程处理
using namespace  std;

class TestLambda{ 
public:
    void start(){
        thread th([this]()
                  { cout << "name = " << name <<" "<<this_thread::get_id()<< endl; });
        th.join();
    }
   
    string name = "TestLambda test";
};
int main(){

    thread th([](int a)
              { cout << "lamada " << a <<" "<< this_thread::get_id() << endl; },
              10);
    th.join();
    cout << "______________" << endl;
    TestLambda p;
    p.start();
    return 0;
}