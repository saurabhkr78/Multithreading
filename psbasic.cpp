#include <bits/stdc++.h>
using namespace std;

// ✅ Custom Comparator for Priority Queue
struct CompareTask {
    bool operator()(const pair<int, function<void()>>& a, const pair<int, function<void()>>& b) {
        return a.first > b.first;
    }
};

class Executor {
    priority_queue<pair<int, function<void()>>, vector<pair<int, function<void()>>>, CompareTask> taskQueue;
    vector<future<void>> futures;
    mutex queueMutex;
    condition_variable cv;
    atomic<bool> isShutdown{false};
    atomic<int> activeTasks{0};
    const int MAX_CONCURRENT_TASKS = 8;

public:
    Executor() {}

    void addTask2Queue(function<void()> task, int priority = 10) {
        {
            lock_guard<mutex> lock(queueMutex);
            taskQueue.push({priority, task});
        }
        cv.notify_one();
        executeTasksAsync();
    }

    void executeTasksAsync() {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> lock(queueMutex);
                if (taskQueue.empty() || isShutdown || activeTasks >= MAX_CONCURRENT_TASKS) return;

                task = taskQueue.top().second;
                taskQueue.pop();
                activeTasks++;
            }

            // ✅ Run asynchronously
            futures.push_back(std::async(launch::async, [this, task]() {
                task();
                activeTasks--;
            }));
        }
    }

    void shutdown() {
        if (isShutdown) return;

        cout << "Shutdown called" << endl;
        {
            lock_guard<mutex> lock(queueMutex);
            isShutdown = true;
        }
        cv.notify_all();

        // ✅ Ensure all tasks are completed
        for (auto& fut : futures) {
            if (fut.valid()) {
                fut.get();
            }
        }
    }

    ~Executor() {
        shutdown();
    }
};

int main() {
    Executor obj;
    cout << "Object created" << endl;

    for (int i = 0; i < 100000000000; i++) {
        obj.addTask2Queue([i] {
            cout << "[Task] " << i << " executed by " << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }, rand() % 10);
    }

    this_thread::sleep_for(chrono::seconds(5));
    obj.shutdown();

    return 0;
}
