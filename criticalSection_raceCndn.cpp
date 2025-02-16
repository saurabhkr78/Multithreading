#include<bits/stdc++.h>
using namespace std;


int shared_memory=0;
void fxn1(){
   shared_memory++;
   cout<<"value:"<<shared_memory<<endl;
  }

int main(){
thread threads[5]; //store thrads
for(int i=0;i<5;i++){
    threads[i]=thread(fxn1);
}
    for(int i=0;i<5;i++){
        threads[i].join();
    }

}

// to avoid the difference in result we use mutex semaphore and lock mechanism.