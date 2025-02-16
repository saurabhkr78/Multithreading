#include<bits/stdc++.h>
using namespace std;

void fxn1(){
  cout<<"fxn 1 executing"<<endl;
  }
 void fxn2(){
   cout<<"fxn 2 executing"<<endl;
 }


int main(){
thread t1(fxn1);
thread t2(fxn2);
t1.join();
t2.join();
}