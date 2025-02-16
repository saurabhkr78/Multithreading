/*
TOPIC: unique_lock In C++ (std::unique_lock<mutex> lock(m1))



NOTES:

1. The class unique_lock is a mutex ownership wrapper andf std::unique_lock<std::mutex> is a more advanced mutex wrapper than std::lock_guard.
It allows more control over locking and unlocking mechanisms.
2.when scope of unique_lock obejct goes out of then unlcoking happens in the destructor of unique lock

2. It Allows:

       a. Can Have Different Locking Strategies

       b. time-constrained attempts at locking (try_lock_for, try_lock_until)

       c. recursive locking

       d. transfer of lock ownership (move not copy)

       e. condition variables.

       f.manual unlocking

       e. we can pass differenent locking strategy by passing it to unique_lock parameter e.g std::unique_lock<std::mutex> lock(mtx, std::defer_lock);



Locking Strategies

   TYPE             EFFECTS(S)

1. defer_lock       do not acquire ownership of the mutex at the same time/immediately. We must call lock() manually.viz,owning the mutex but not locking it. so in this case it is better than lock guard. but locked explicitly.

void example() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);  // Do not lock immediately
    // Some computations before locking...
    lock.lock();  // Manually lock later
}


2. try_to_lock      try to acquire ownership of the mutex without blocking so if u r not able to lock the mutex it wont wait for that mutex and go ahead

void example() {
    std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);
    if (lock.owns_lock()) {  // Check if the mutex was successfully locked
        cout << "Mutex locked successfully!" << endl;
    } else {
        cout << "Mutex was already locked!" << endl;
    }
}



3. adopt_lock       assume the calling thread already has ownership of the mutex.


void example() {
    mtx.lock();  // Manually lock before creating unique_lock
    std::unique_lock<std::mutex> lock(mtx, std::adopt_lock);  // Take ownership of already locked mutex
}


bool tryLock() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    if (lock.try_lock_for(chrono::milliseconds(100))) {  // Wait for 100ms to acquire the lock
        cout << "Lock acquired!" << endl;
        return true;
    } else {
        cout << "Could not acquire lock!" << endl;
        return false;
    }
}


*/


#include <bits/stdc++.h>
using namespace std;

std::mutex mtx;
int counter = 0;

void solve() {
    std::unique_lock<std::mutex> lock(mtx);  // Locks the mutex
    for (int i=0;i<10;i++) {
        counter++;
        cout << "Thread " << this_thread::get_id() << " incremented counter: " << counter << endl;
    }


}

int main() {
    thread t1(solve);
    thread t2(solve);

    t1.join();
    t2.join();

    cout << "Final Counter: " << counter << endl;
    return 0;
}




