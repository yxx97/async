/*
    RAII resource acquisition is initialization
    使用局部对象来管理资源的技术成为资源获取即初始化；它的生命周期有操作系统来管理的，无需人工介入
    资源销毁容易忘记，造成死锁或内存泄漏
*/
#include<iostream>
#include<mutex>
#include<thread>
#include<string>
#include<shared_mutex>
using namespace std;
class XMutex{
    public:
    XMutex(mutex& mux):mux_(mux){
        cout << "Lock" << endl;
        mux.lock(); 
    }
    ~XMutex(){
        cout << "Unlock" << endl;
        mux_.unlock();
    }
    private:
        mutex &mux_;
};
static mutex mux;
void TestMutex(int status){
    XMutex lock(mux);
    if(1==status){
        cout << "=1" << endl;
        return;
    }else{
        cout << "!=1" << endl;
        return;
    }
}

/*
    lock_guard
    c++11 实现严格基于作用域的互斥所有权包装器
    adopt_lock c++ 11 类型为adopt_lock_t ，假设调用方已拥有互斥的所用权
    通过{}控制锁的临界区

*/
static mutex gmutex;
void TestLockGuard(int i){
    gmutex.lock();
    {
        //已经拥有锁，不lock
        lock_guard<mutex> lock(gmutex, adopt_lock);
        //结束释放锁
    }
    {
        lock_guard<mutex> lock(gmutex);
        cout << "begin thread" << endl;
    }

    for (;;){

        {
            lock_guard<mutex> lock(gmutex);
            cout << "In" << i << endl;
        }
        this_thread::sleep_for(500ms);
    }
}

/*
    unique_lock C++11 实现可移动的互斥锁所有权包装器
    支持临时释放锁unlock
    支持adopt_lock(已经拥有锁，不加锁，出栈区会释放)
    支持defer_lock(延后拥有，不加锁，出栈区不释放)
    支持try_to_lock尝试获取互斥的所有权而不阻塞，获取失败退出栈区不会释放，通过owns_lock()函数判断
*/ 
void func(){

    {
        static mutex mux;
        {
            unique_lock<mutex> lock(mux);
            lock.unlock();
            lock.lock();
        }
        {
            //已经拥有锁，不锁定，退出栈区解锁
            mux.lock();
            unique_lock<mutex> lock(mux,adopt_lock);
           
        }
        {
            //延后加锁 不拥有 退出栈区不加锁
            unique_lock<mutex> lock(mux,defer_lock);
            //加锁，退出栈区解锁
            lock.lock();
        }
        {
            //尝试加锁 不阻塞 失败不拥有锁
            unique_lock<mutex> lock(mux,try_to_lock);
            if(lock.owns_lock()){
                cout << "owns_lock" << endl;
            }else{
                cout << "not owns_lock" << endl;
            }
            
        }
    }
}
int main(){
    // TestMutex(1);
    // TestMutex(2);
    /*
        for (int i = 0; i < 3;++i){
            thread th(TestLockGuard, i + 1);
            th.detach();
        }
    */
    func();
    getchar();
    return 0;
}