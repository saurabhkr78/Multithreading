/*
1.Scoped_lock(mtx1,mtx2....) try to lock all the mutex and their criticl section
2. if there is any deadlock in critical section it has inbuilt deadlock avoidance mechanism implmented in it.



*/



#include<iostream>
#include<thread>
#include<mutex>
using namespace std;


mutex mtx1,mtx2;

void process(int id){
    scoped_lock lock(mtx1,mtx2);

    cout<<"Thread "<<id<<" is processing with  mtx1 and mtx2"<<endl;
}


int main(){
    const int numThreads = 100;
    thread threads[numThreads];

    for(int i=0;i<numThreads;i++){
        threads[i] = thread(process,i);
    }

    for(int i=0;i<numThreads;i++){
        threads[i].join();
    }
    return 0;
}