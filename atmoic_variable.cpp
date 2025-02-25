/*
at all the time only one thread is allowed to perform operations on the atomic variable.
atomic variable are used to avoid race condition instead of locking and unlocking the mutex we can use atomic variable for trivial task.


*/

#include <iostream>
#include <thread>
#include <atomic>
#include<mutex>

using namespace std;


std::atomic<int> cnt(0);
int times=100000;


void run(){
    for(int i=0;i<times;i++){
        ++cnt;
    }
}
int main(){


    thread t1(run);
    thread t2(run);

    t1.join();
    t2.join();

    cout << "Final cnt value: " << cnt.load() << endl; 
    cout<<cnt<<endl;
    return 0;
}