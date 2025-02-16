/*
NOTES:

1. Condition variables allow us to synchronize threads via notifications.

   a. notify_one();

   b. notify_all();

2. You need mutex to use condition variable

3. Condition variable is used to synchronize two or more threads.

4. Best use case of condition variable is Producer/Consumer problem.

5. Condition variables can be used for two purposes:

    a. Notify other threads

    b. Wait for some condition
 */

#include <bits/stdc++.h>
using namespace std;

std::condition_variable cv;
std::mutex mtx;
int balance = 0;

// Correct function to check balance
bool checkBalance() {
    return balance > 0;
}

void deposit(int amt) {
    std::unique_lock<std::mutex> lock(mtx);
    balance += amt;
    cout << "Amount added and Current Balance is: " << balance << endl;
    cv.notify_one();  // Notify waiting thread
}

void withdraw(int amt) {
    std::unique_lock<std::mutex> lock(mtx);

    // Wait until condition get verified
    cv.wait(lock, checkBalance);// can use lambda fxn here bool checkBalance() { return balance > 0; }

    if (balance >= amt) {
        balance -= amt;
        cout << "Amount deducted: " << amt << " | Current Balance: " << balance << endl;
    } else {
        cout << "Balance is less than the withdrawal amount!" << endl;
    }
}

int main() {
    std::thread t2(withdraw, 50);
    std::thread t1(deposit, 100);

    t1.join();
    t2.join();

    return 0;
}
