// Include necessary headers for threading, synchronization, and data structures
#include <iostream>
#include <vector>
#include <queue>
#include <functional>  // For std::function
#include <mutex>       // For thread synchronization
#include <condition_variable>
#include <thread>
#include <atomic>      // For atomic operations

using namespace std;

/*
    Thread Pool Class (Executor)
    - Manages a group of worker threads
    - Maintains a queue of tasks to execute
    - Handles task distribution and thread synchronization
*/
class Executor {
private:
    // Member Variables
    vector<thread> threads;          // Container for worker threads
    queue<function<void()>> tasks;   // Task queue storing functions to execute
    mutex task_mutex;                // Protects access to the task queue
    condition_variable cv;           // Coordinates thread wake/sleep
    atomic<bool> stop;               // Thread-safe flag for shutdown

public:
    // Constructor: Creates worker threads
    Executor(size_t num_threads = thread::hardware_concurrency())
        : stop(false)  // Initialize stop flag to false
    {
        // Create specified number of worker threads
        for (size_t i = 0; i < num_threads; ++i) {
            // Each thread runs the ExecuteTask member function
            threads.emplace_back(&Executor::ExecuteTask, this);
        }
    }

    // Destructor: Ensures proper cleanup
    ~Executor() {
        shutdown();
    }

    // Submit a task to the thread pool
    void SubmitTask(function<void()> fn) {
        {
            // Lock the task queue for safe access
            lock_guard<mutex> lock(task_mutex);

            // Add the task to the queue
            tasks.push(fn);
        }

        // Notify one waiting thread that a task is available
        cv.notify_one();
    }

    // Main worker thread function
    void ExecuteTask() {
        while (true) {
            function<void()> task;

            {
                // Wait until tasks are available or shutdown is requested
                unique_lock<mutex> lock(task_mutex);
                cv.wait(lock, [this]() {
                    return stop || !tasks.empty();
                });

                // Exit if shutdown requested and queue is empty
                if (stop && tasks.empty()) return;

                // Get the next task from the queue
                if (!tasks.empty()) {
                    task = tasks.front();
                    tasks.pop();
                }
            }

            // Execute the task outside the lock
            if (task) task();
        }
    }

    // Shut down the thread pool gracefully
    void shutdown() {
        // Set stop flag
        stop = true;

        // Wake up all threads
        cv.notify_all();

        // Wait for all threads to finish
        for (auto& t : threads) {
            if (t.joinable()) t.join();
        }
    }

    // Get current number of pending tasks
    size_t GetQueueSize() {
        lock_guard<mutex> lock(task_mutex);
        return tasks.size();
    }

    // Check if shutdown has been requested
    bool shutdown_requested() const {
        return stop.load();
    }
};

// Main program demonstrating thread pool usage
int main() {
    // Create thread pool with default number of threads
    Executor executor;

    // Thread-safe counter to track completed tasks
    atomic<int> counter{0};

    // Number of tasks to process (1 million)
    const int NUM_TASKS = 1000000;

    // Create a task producer thread
    thread producer([&]() {
        for (int i = 0; i < NUM_TASKS; ++i) {
            // Submit task to increment counter
            executor.SubmitTask([&]() {
                counter++;
            });
        }
    });

    // Create monitoring thread
    thread monitor([&]() {
        while (true) {
            // Exit condition: shutdown requested and queue empty
            if (executor.shutdown_requested() &&
                executor.GetQueueSize() == 0) break;

            // Print current status every 100ms
            cout << "Tasks in queue: " << executor.GetQueueSize()
                 << " | Completed tasks: " << counter.load() << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });

    // Wait for producer to finish submitting tasks
    producer.join();

    // Wait for monitor to finish
    monitor.join();

    // Shut down thread pool
    executor.shutdown();

    // Final output
    cout << "\nAll tasks completed!\n";
    cout << "Final counter value: " << counter << endl;

    return 0;
}