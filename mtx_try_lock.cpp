/*

try_lock()

1.try_lock tries to lock to lock the mutex it returns immediateky ,on successful lock return true else false,
unlike mutex.lock() it creates blocking condition that's why mtx_lock() is called non - blocking.
2. if a thread own the mutex and again try_lock is again called by same thread then the behaviour of the thread is undefined and deadlock situation. 
3. the solution for the above problem is recursive mutex.

There are so many try_lock function
1. std::try_lock
2. std::mutex::try_lock
3. std::shared_lock::try_lock
4. std::timed_mutex::try_lock
5. std::unique_lock::try_lock
6. std::shared_mutex::try_lock
7. std::recursive_mutex::try_lock
8. std::shared_timed_mutex::try_lock
9. std::recursive_timed_mutex::try_lock

*/


#include<bits/stdc++.h>
using namespace std;

int cnt=0;

std::mutex mtx;
void increase(){
    for(int i=0;i<1000000000;i++){
        if(mtx.try_lock()){
            ++cnt;
            mtx.unlock();
        }
       
    }
}
int main(){
std::thread t1(increase);
std::thread t2(increase);
t1.join();
t2.join();
cout<<"counter:"<<cnt;
    return 0;
}
/*
 not seeing any output because your loop runs 1 billion times per thread (1000000000 iterations), which takes a massive amount of time due to contention on std::mutex. Since try_lock() only locks if the mutex is free, one thread might fail repeatedly, slowing things down even more.
 */