#include<iostream>
#include<string>
#include<thread>

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
void MainThrad(Para& p ){
    this_thread::sleep_for(1s);
    cout << p.name << endl;
}

int main(){

    {
        Para p;
        p.name = "test ref";
        //引用必须加上 ref
        thread th(MainThrad, ref(p));
        th.join();
    }
    getchar();
    return 0;
}