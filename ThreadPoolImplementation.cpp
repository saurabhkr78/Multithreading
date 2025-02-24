// thread pool is a pool of thread where multiple threads are wating as soon as you give them task they starts executing
// in order to execute the task in parallel need to spawn the thread lets supoose you have 10k task you can't directly create 10k threads it will choke the system
// we have thread pool we schedule the task ,assign the task to thread pool , and thread pool task is to pick the task from the queue and assign it to different different threads how many it have ,it will schedule to those threads
//you have control to create n numbers of thread in thread pool
//it's depenedent on system how many thread will have in your thread pool for a system with 8 core may have 8 threads
//like we can't create and destroy thread each time so we have threadpool

#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>


//TODO:add generic task to thread pool

using namespace std;

class Threadpool {
private:
    int m_threads;
    vector<thread> threads;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable cv;
    bool stop = false;

public:
    explicit Threadpool(int numThreads) : m_threads(numThreads), stop(false) {
        for (int i = 0; i < m_threads; i++) {
            threads.emplace_back([this] { // Lambda function for thread
                while (true) {
                    function<void()> task;
                    unique_lock<mutex> lock(mtx);
                    cv.wait(lock, [this] {
                        return !tasks.empty() || stop;
                    });

                    if (stop && tasks.empty()) return; // Ensure all tasks are completed before stopping

                    // Print size before processing a task
                    cout << "[THREAD] Processing task, queue size before pop: " << tasks.size() << endl;

                    task = move(tasks.front());
                    tasks.pop();
                    
                    lock.unlock();

                    task();
                }
            });
        }
    }

    ~Threadpool() {
        unique_lock<mutex> lock(mtx);
        stop = true;
        lock.unlock();
        cv.notify_all();

        for (auto& th : threads) {
            if (th.joinable()) th.join();
        }
    }

    void ExecuteTask(function<void()> func) {
        unique_lock<mutex> lock(mtx);
        tasks.push(func);

        // Print size after adding a task
        cout << "[MAIN] Task added, queue size: " << tasks.size() << endl;

        lock.unlock();
        cv.notify_one();
    }
};

void fxn() {
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Hello World" << endl;
}

int main() {
    Threadpool pool(8); // Create the thread pool once

    while (true) { // Infinite tasks
        pool.ExecuteTask(fxn);
        this_thread::sleep_for(chrono::milliseconds(500)); // Prevent excessive looping
    }

    cout << "Thread pool implementation finished" << endl;
    return 0;
}




