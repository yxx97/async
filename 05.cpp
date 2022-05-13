#include<iostream>
#include<string>
#include<thread>
using namespace std;

class MyThread{
    public:
    void Main(){
        cout << "MyThread Main" << name << ":" << age << endl;
    }
    string name;
    int age = 100;
};


class XThread{
public:
    virtual void start(){
        is_exit_ = false;
        th_ = std::thread(&XThread::Main,this);
    }
    virtual void stop(){
        is_exit_ = true;
        Wait();
    }
    virtual void Wait(){
        if(th_.joinable()){
            th_.join();
        }
    }
    bool is_exit() {
        return is_exit_;
    }
private:
    virtual void Main() = 0;
    std::thread th_;
    bool is_exit_ = false; 
};


class  TestXThread : public XThread{
    public:
    void Main() override{
        cout << "testxhtread main begin" << endl;
        while(!is_exit()){
            this_thread::sleep_for(100ms);
            cout << "." << flush;
        }
        cout << "testxhtread main end" << endl;
    }
    string name;
};

int main(){


    TestXThread testth;
    testth.name = "testthread name";
    testth.start();
    this_thread::sleep_for(2s);
    testth.stop();
    testth.Wait();
    getchar();

    // MyThread myth;
    // myth.name = "test name 05";
    // myth.name = 20;
    // //这里的函数必须取地址，
    // thread th(&MyThread::Main, &myth);
    // th.join();
}
