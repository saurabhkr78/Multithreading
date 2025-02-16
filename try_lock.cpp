/*
1.try_lock () is different from mutex lock
2.it's a fxn which tries to lock all the lockable object passed to it
e.g std::try_lock(m1,m2,m3,m4..mn);
3. it tries to lock an obkject is successfully locked then return -1 else 0-based indexing which object was not able to locked.
4. if failed to lock any of the given objec then it releases all the prev locked obj.
5.If a call to try_lock results in an exception, unlock is called for any locked objects before rethrowing.
6.std::try_lock() is a special function that tries to lock multiple mutexes at once without blocking.

*
*/

#include<bits/stdc++.h>
using namespace std;

std::mutex mtx1,mtx2;
void solve(){
  int res;
  while((res=std::try_lock(mtx1,mtx2))!=-1){
  cout<<"mutex"<<res<<"failed to lock...trying to lock\n";
  std::this_thread::yield();//let other threads run by yield function
  }
  cout<<"both mutexes locked successfully by thread\n"<<this_thread::get_id()<<endl;

  mtx1.unlock();
  mtx2.unlock();


  }


int main(){
  std::thread t1(solve);
  std::thread t2(solve);
  t1.join();
  t2.join();
  return 0;
  }