/*
promise 和future
    promise用于异步传输变量
        std::promise提供存储异步通信的值,再通过其对象创建的std::future异步获取结果.
        std::promise只能使用一次.void set_value(_Ty&&_Val)设置传递值,智能调用一次
    std::future 提供访问异步操作结果的机制
        get()阻塞等待promise set_value 的值 设计的是一种移动语义 只能调用一次
    std::shared_future
        get() 是复制内容 而不是转移    
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

void TestFuture(promise<string> p){
    cout << "being TestFuture" << endl;
    this_thread::sleep_for(3s);
    cout << "begin set value" << endl;\
    //只要这边设值了 future.get()就不堵塞
    p.set_value("yxx handsome");
    this_thread::sleep_for(3s);
    cout << "end TestFuture" << endl;
}

int main(){
    promise<string> p;
    //shared_future<string> result_s = shared_future<string>(p.get_future());
    auto result = p.get_future();
    auto th = thread(TestFuture, move(p));

    cout << "begin future.get()" << endl;

    //判断是否result有值
    bool ifcanget = result.valid();

    //shared_future<string> result_s = shared_future<string>(std::move(result));
    shared_future<string> result_s = shared_future<string>(result.share());
    // future.get() 的设计是一个移动语义，所以如果第一次执行完get（）后再调用get 会异常
    cout << "future get() = " << result_s.get()<<endl;
    cout << result_s.get() << endl;
    cout << "end future.get()" << endl;
    th.join();

    return 0;
}