/*
std::lock() In C++11 It is used to lock multiple mutex at the same time.

And the syntax is as follow:
std::lock(m1, m2, m3, m4);
1. All arguments are locked via a sequence of calls to lock(),  try_lock(), or unlock() on each argument.
2. Order of locking is not defined (it will try to lock provided mutex in any order and ensure that
    there is no deadlock).
3. It is a blocking call.

[Example:0] -- No deadlock.
    Thread 1                    Thread 2
    std::lock(m1,m2);           std::lock(m1,m2);

[Example:1] -- No deadlock.

    Thread 1                    Thread 2
    std::lock(m1, m2);          std::lock(m2, m1);


because as the t1 locked m1  and t2 locked m2 in 1sec. In the very next second when t1 will try to lock m2 but it was already locked by t2 so t1 will release the m1 and let t2 get execute and let it unlock() m2 till then t1 will wait for m2 to get released.

[Example:2] -- No deadlock.

    Thread 1                    Thread 2
    std::lock(m1, m2, m3, m4);  std::lock(m3, m4);
                                std::lock(m1, m2);

[Example:3] -- Yes, the below can deadlock.

    Thread 1                    Thread 2
    std::lock(m1,m2);           std::lock(m3,m4);
    std::lock(m3,m4);           std::lock(m1,m2);









1.std::lock(m1, m2); (Safe)
Locks both mutexes atomically (no fixed order).
Avoids deadlock automatically by retrying if locking order is an issue.
Works well when multiple threads may lock mutexes in different orders.
When multiple mutexes are involved


2.m1.lock(); m2.lock(); (Risky)
Locks m1 first, then m2 sequentially.
If another thread locks m2 first and m1 second, both threads get stuck in a deadlock.
Must manually unlock in reverse order.
When mutex locking order is guaranteed to be safe
Use std::adopt_lock with std::lock_guard when using std::lock()













*/


#include<bits/stdc++.h>
using namespace std;

std::mutex m1,m2;

void task1(){
    while (true){
        lock(m1,m2);
        cout<<"task 1"<<endl;
        m1.unlock();
        m2.unlock();
    }

  }
void task2(){
    while (true) {
        lock(m2,m1);
        cout<<"task 2"<<endl;
        m2.unlock();
        m1.unlock();
    }

}
int main(){
  thread t1(task1);
  thread t2(task2);
  t1.join();
  t2.join();
  return 0;
}
