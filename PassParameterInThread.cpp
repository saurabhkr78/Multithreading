#include<bits/stdc++.h>
using namespace std;

void add(int x,int y){
  cout<<"addition of two number is"<<x+y<<endl;
  }
 void multiply(int x,int y){
   cout<<"multiplication of two number is"<<x*y<<endl;
 }
int main(){
int x,y;
cin>>x>>y;
thread t1(add,x,y);
thread t2(multiply,x,y);
t1.join();
t2.join();
return 0;




}