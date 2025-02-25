/*
This video explains **oversubscription in multithreading** in a practical way. Here’s a summary with key points:



What is Oversubscription?
- Normally, the **number of threads** should match the **number of CPU cores** for optimal performance.
- Example: If a CPU has **4 cores**, having **4 threads** ensures each thread runs on a separate core without waiting.


Why Oversubscription Happens?
- If you create **more threads than CPU cores**, some threads must **wait** for CPU time.
- The OS **scheduler** constantly switches between these threads, which may reduce performance.



When is Oversubscription Useful?
- **For I/O-bound tasks** (e.g., reading files, network calls, database queries).  
- If a thread **waits (blocks)** for a long time, the CPU **stays idle**.  
- By **adding more threads**, we can keep the CPU **busy** while some threads are waiting.

Example:
- A web server processing requests.  
- Some threads wait for database responses.  
- Extra threads **keep CPU occupied** while waiting threads are idle.

---

When to Avoid Oversubscription?
- **For CPU-bound tasks** (heavy calculations, simulations, game physics).  
- Too many threads cause **frequent switching**, making things **slower** instead of faster.  

Example:
- A program doing **matrix multiplications** with **8 CPU cores** should ideally use **8 threads**.  
- If we use **16 threads**, the CPU spends too much time **switching** instead of calculating.

---

Best Practices
- **Default:** Use **# of CPU cores** = **# of threads**.  
- **For I/O-bound tasks:** Add **extra threads** (e.g., 2x CPU cores).  
- **Measure Performance:** Use profiling tools to check if adding threads **helps** or **slows down** execution.

---

- Oversubscription **is useful for I/O-heavy tasks** but **bad for CPU-heavy tasks**.
- **More threads ≠ always faster** The key is to **balance** the workload.  




What is Oversubscription?
Oversubscription happens when we create more threads than the CPU can handle efficiently. This makes the system slow because too many threads are fighting for CPU time.

Why Does Oversubscription Happen?
Too Many Threads – If we create more threads than the number of CPU cores, they start competing for execution time.
Misconfigured Thread Pools – If thread pools are not properly set, they may create too many active threads.
Threads Waiting for I/O – If many threads are waiting for input/output (disk, network), they take up memory but do no real work.
Too Many Running Applications – If multiple apps create many threads, they slow each other down.
Misuse of Hyperthreading – Hyperthreaded cores are not as powerful as physical cores, so we shouldn't assume they can handle the same number of threads.
What Problems Does It Cause?
Too Much Switching – The CPU keeps switching between threads, wasting time instead of doing actual work.
Slow Performance – The CPU cache (fast memory) gets misused due to frequent switches.
High Memory Usage – More threads mean more memory is needed, causing slowdowns.
More Waiting Time – Too many threads competing for shared resources (e.g., files, database) leads to delays.
Unfair CPU Usage – Some threads may get little or no CPU time while others dominate.
How to Avoid Oversubscription?
Use the Right Number of Threads

CPU-based tasks → Use threads equal to the number of CPU cores.
I/O-based tasks → Use more threads, but not too many (about 2x CPU cores).
Use built-in functions like:
C++ → std::thread::hardware_concurrency()
Java → Runtime.getRuntime().availableProcessors()
Use Thread Pools Instead of Creating Threads Manually

Instead of creating a new thread for every task, use a thread pool that reuses existing threads.
Example: Java (ThreadPoolExecutor), C++ (std::async).
Distribute Work Evenly

Make sure all threads get a fair amount of work to avoid overloading some while others are idle.
Reduce Waiting (Blocking)

If threads spend too much time waiting for resources, they waste CPU time.
Use asynchronous programming or lock-free data structures.
Monitor Performance and Adjust

Use tools like Task Manager (Windows), htop (Linux), or perf to see CPU load.
Adjust the number of threads based on how your program behaves.



*/