/*
1.Automatically locks the mutex when the lock_guard object is created.
2.Automatically unlocks the mutex when the lock_guard object goes out of scope (end of function/block).
3.Prevents manual unlocking—you cannot call .unlock() explicitly.
4. Non-copyable—You cannot copy or assign std::lock_guard objects
5.Lightweight and fast—Suitable for simple, short-lived locks.
6.lock guard is an wrapper of owning mutex on scope basis like for loop scope is upto {} only.
*/
#include <bits/stdc++.h>
using namespace std;

std::mutex mtx;  // Mutex to protect shared resource
int counter = 0;

void safeIncrement() {
    std::lock_guard<std::mutex> lock(mtx);  // Lock mutex automatically
    counter++;  // Critical section (safe increment)
    cout << "Thread " << this_thread::get_id() << " incremented counter: " << counter << endl;
}

int main() {
    thread t1(safeIncrement);
    thread t2(safeIncrement);

    t1.join();
    t2.join();

    cout << "Final Counter: " << counter << endl;
    return 0;
}
