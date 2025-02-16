#include <bits/stdc++.h>
using namespace std;

// Global shared resource
int bal = 100;
mutex mtx; // Mutex is a synchronization technique used to avoid race conditions and protect resources when accessed by multiple threads.
// To avoid access by multiple threads when one thread is already accessing it.
// Mutex is also a shared resource.

// Deposit function (dep1)
void dep1(int amt) {
    mtx.lock(); // Blocking call by acquiring mutex
    int temp = bal;
    temp += amt;
    bal = temp;  // Updating shared resource
    mtx.unlock(); // Unlocking the mutex to allow other threads to access
}

// Deposit function (dep2)
void dep2(int amt) {
    mtx.lock();
    int temp = bal;
    temp += amt;
    bal = temp;
    mtx.unlock();
}

// Withdraw function to demonstrate race condition prevention
void withdraw(int amt) {
    mtx.lock();
    if (bal >= amt) {
        int temp = bal;
        temp -= amt;
        bal = temp;
        cout << "Withdrawal of " << amt << " successful. Remaining balance: " << bal << endl;
    } else {
        cout << "Insufficient balance! Current balance: " << bal << endl;
    }
    mtx.unlock();
}

int main() {
    cout << "Initial Balance: " << bal << endl;

    // Creating threads to simulate concurrent access
    thread t1(dep1, 50);  // Thread to deposit 50
    thread t2(dep2, 70);  // Thread to deposit 70
    thread t3(withdraw, 80); // Thread to withdraw 80

    // Joining threads to ensure completion
    t1.join();
    t2.join();
    t3.join();

    cout << "Final Balance: " << bal << endl; // Display final balance after all transactions

    return 0;
}
