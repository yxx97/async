#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<sstream>
#include<list>
#include<shared_mutex>
using namespace std;
/*
    生产者消费者模型 
    生产者和消费者共享资源变量
    生产者生产一个产品，通知消费者消费
    消费者阻塞等待信号  获取信号后消费产品(去除list队列中数据)
*/

/*
    unique_lock(mutex);
    cv.wait(lock,lambda);
    只有lambda表达式为true才回去wait 

*/
list<string> msg_;
mutex mux;
condition_variable cv;
void ThreadWrite()
{
    for (int i = 0;;i++)
    {
        stringstream ss;
        ss << "write mes" << i;
        unique_lock<mutex> lock(mux);
        msg_.push_back(ss.str());
        mux.unlock();
        //发送信号
        cv.notify_one();
        this_thread::sleep_for(3s);
    }
}
void ThreadRead(int i)
{
    for (;;)
    {
        cout << "read mes" << endl;
        unique_lock<mutex> lock(mux);
        //cv.wait(lock);//解锁 阻塞等待信号

        cv.wait(lock, [i]
                {
                    cout << i << "wait" << endl;
                    //return false;
                    return !msg_.empty();
                });
        //获得信号后锁定
        while (!msg_.empty())
        {
            cout << i << "read " << msg_.front() << endl;
            msg_.pop_front();
        }
        
    }
}
int main()
{
    thread th(ThreadWrite);
    th.detach();
    for (int i = 0; i < 3;++i){
        thread th(ThreadRead, i + 1);
        th.detach();
    }
    getchar();
    return 0;
}