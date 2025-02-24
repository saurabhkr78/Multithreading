/* 
THE PROBLEM STATEMENT:
 1. Producer will produce and consumer will consume with synchronisation of a common buffer.
 2. Until producer thread produces any data consumer thread can't consume.
 3. Threads will use condition_variable to notify each other.
 4. We need mutex if we use condition_variable because CV waits on mutex.
 5. This is one of the example of producer consumer there are many.

PRODUCER thread steps:
 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
 2. check if buffer is full and if it is full then unlock mutex and sleep, if not then go ahead and produce.
 3. insert item in buffer.
 4. unlock mutex. 
 5. notify consumer.

CONSUMER thread steps:
 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
 2. check if buffer is empty and if it is, then unlock the mutex and sleep, if not then go ahead and consume.
 3. consume item from buffer.
 4. unlock mutex.
 5. notify producer.

IMP:
 Producer and Consumer have to notify each other upon completion of their job.



 producer threads t1,t2,t3,t4,t5 producing data ->buffer storage->consumer threads t1 cosuming data;
both try to access buffer at the same time.

steps:
producer took the look using mutex and produced the data ,unlock the mutex and notify the consumer using condition variable and consumer will consume the data and notify the producer using condition variable.

 */

#include<bits/stdc++.h>
using namespace std;
std::mutex mtx;
std::condition_variable cv;
deque<int> buffer;
int buffer_size=50;

void producer(int val){
    while(val){
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck,[](){return buffer.size()<buffer_size;});//before producing data producer will check if buffer is full or not. If buffer is full then producer will wait. and if buffer is full then producer will wait by releasing the lock.
        buffer.push_back(val);
        cout<<"produced "<<val<<endl;
        val--;
        lck.unlock();
        cv.notify_one();//if number of consumer is 1 then notify_one is enough else notify_all() is needed.


    }
}
void consumer(){
    while(true){
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck,[](){return buffer.size()>0;});//before consuming data consumer will check if buffer is empty or not. If buffer is empty then consumer will wait. if buffer is empty then consumer will wait by releasing the lock.
        int val=buffer.back();
        buffer.pop_back();
        cout<<"consumed "<<val<<endl;
        lck.unlock();
        cv.notify_all();//if number of producer is 1 then notify_one is enough else notify_all() is needed.
    }
}
int main(){
    thread t1(producer,100);
    thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}
//consumer and producer will have same mutex they can't have different mutex.it's like having a single key for a common place.if mutiple people can have multiple keys then it's not a common place.if you want to sync your data among all the threads then there should be a common mutex.
// it depends on the cpu which thread will get the lock first either producer or consumer.both are running in loop so it's not guaranteed that producer will produce first and consumer will consume first.
// if data produced by producer is consumed by consumer and lock is released by consumer till then consumer thread will sleep automatically then producer will get the lock and produce the data and consumer will consume the data and so on.