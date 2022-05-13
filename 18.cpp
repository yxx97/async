/*
    async
    c++11 异步运行一个函数,并返回保有其结果的std::future
    a)launch::deferred 延迟执行 当在调用wait和get时,调用函数代码
    b)launch::async 创建线程(默认)
    c)launch::deferred|launch::async 这里调用async的行为可能是 创建新线程立即执行或者 没有创建新线程并且延迟到get()才开始执行入口函数 两者居其一
    d)不带额外参数默认值应该是和c一模一样 系统会自行决定是异步(创建新线程)还是同步执行(不创建新线程)

    自行决定啥意思？
    std::async 和 std::thread
    std::thread 创建线程 如果资源紧张，创建线程失败，那么整个程序会异常崩溃 如果线程返回值 你先拿到这个值也不容易 可以通过全局变量来得到
    std::async 创建异步任务 可能创建也可能不创建线程 并且async调用方法容易得到线程入口函数的返回值 future
    (1)std::thread 创建的线程太多，则可能失败，系统报告异常，崩溃
    (2)std::async 一般不会报异常，因为如果系统资源紧张导致无法创建新线程的时候，std::async这种不加额外函数的调用
        就不会创建新线程而是后续谁调用了get() 就执行在谁调用的线程上，不自己创建线程了
    (3) 一个程序中  线程数量不易超过100-200。

    不见额外参数的async调用 让系统自己决定是否创建新线程
    所以这个任务到底有没有被推迟执行 可以用wait_for(0s) 来判断

    返回的线程函数的返回值类型的std::future<int> (std::future<线程函数的返回值类型>)
    re.get()获取结果,会阻塞等待
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

string TestAsync(int i){
    cout << "TestAsync kaishi " << endl;
    cout << i <<" "<< this_thread::get_id() << endl;
    this_thread::sleep_for(1s);
    return "yxx one";
}
int main(){

    // cout<<this_thread::get_id()<<endl;
    // //表示延迟 不创建线程 在主线程中执行
    // auto future = async(launch::deferred, TestAsync, 10);
    // this_thread::sleep_for(4s);

    // //当调用get的时候才开始调用
    // cout << future.get() << endl;

    //默认是创建线程的
    // 如果没执行完这个线程，最后main函数会等待这个线程运行完才返回
    auto future2 = async(TestAsync, 11);

    //会阻塞在这等
    std::future_status status = future2.wait_for(chrono::seconds(1)); //等待一秒
    if(status == std::future_status::timeout){ //超时 我想等待一秒 希望你返回 你没有返回 那么status==timeout

    }
    else if(status == future_status::ready){
        //表示线程成功返回
    }
    else if(status == future_status::deferred){
        //如果创建线程时设置了launch::deferred 此条件成立  
    }

    this_thread::sleep_for(4s);
    cout << "kaishi" << endl;
    cout << future2.get() << endl;
    getchar();   
    return 0;
}