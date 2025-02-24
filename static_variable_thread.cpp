// // static variable are thread safe untill unless mutex is applied
//
//
// #include<bits/stdc++.h>
// using namespace std;
//
// static int a=0;
//
// void solve(){
//     int cnt=10000;
//
// while(cnt--){
//     ++a;
//
// }
//     cout<<a<<endl;
// }
//
// int main(){
//
//    thread t1(solve);
//     thread t2(solve);
//
//     t1.join();
//     t2.join();
//
//     return 0;
// }


//now lets apply mutex

// static variable are thread safe untill unless mutex is applied


#include<bits/stdc++.h>
using namespace std;

static int a=0;
std::mutex mtx;
void solve(){
    int cnt=10000;
    mtx.lock();
    while(cnt--){
        ++a;

    }
    mtx.unlock();
    cout<<a<<endl;
}

int main(){

    thread t1(solve);
    thread t2(solve);

    t1.join();
    t2.join();

    return 0;
}