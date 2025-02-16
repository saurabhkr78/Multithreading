/*
TOPIC: Recursive Mutex In C++ (std::recursive_mutex)
NOTES:
It is same as mutex but, Same thread can lock one mutex multiple times using recursive mutex.
If thread T1 first call lock/try lock on recursive mutex ml, then ml is locked by T1, now
as T1 is running in recursion Ti can call lock/try lock any number of times there is no issue.
But if T1 have aquired 10 times lock/try lock on mutex ml then thread T1 will have to unlock
it 18 times otherwise no other thread will be able to lock mutex ml.
It means recursive mutex keeps count how many times it was locked so that many times it should be unlocked.
How many time we can lock recursive mutex is not defined but when that number reaches and if we were calling
lock() it will return std::system error OR if we were calling try_lock() then it will return false.
BOTTOM LINE:
It is similar to mutex but have extra facitility that it can be locked multiple time by same thread.
If we can avoid recursive mutex then we should becuase it brings overhead to the system.
It can be used in loops also.
*/


#include <bits/stdc++.h>
using namespace std;

std::recursive_mutex rmtx;

void recursiveFunction(int n) {
    if (n == 0) return;

    rmtx.lock();  // Lock the recursive mutex
    cout << "Thread " << this_thread::get_id() << " locked: " << n << endl;

    recursiveFunction(n - 1);  // Recursive call

    cout << "Thread " << this_thread::get_id() << " unlocking: " << n << endl;
    rmtx.unlock();  // after base cndn hit the thread will  Unlock itself
}

int main() {
    thread t1(recursiveFunction, 3);
    thread t2(recursiveFunction, 3);

    t1.join();
    t2.join();

    return 0;
}
