#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

void add50Nums() {
  int num = 0;
  for (int i = 0; i <= 50; i++) {
    num += i;
  }
  cout << "Addition of 50 numbers is: " << num << endl;
}

void add100Nums() {
  int num = 0;
  for (int i = 0; i <= 100; i++) {
    num += i;
  }
  cout << "Addition of 100 numbers is: " << num << endl;
}

int main() {
  time_point<system_clock> start, end;

  // Sequential execution timing
  start = system_clock::now();
  add50Nums();
  add100Nums();
  end = system_clock::now();
  cout << "Time taken by sequential execution: "
       << duration_cast<microseconds>(end - start).count() << " µs" << endl;

  // Parallel execution using threads
  start = system_clock::now();
  thread t1(add50Nums);
  thread t2(add100Nums);

  t1.join();
  t2.join();

  end = system_clock::now();
  cout << "Time taken by thread execution: "
       << duration_cast<microseconds>(end - start).count() << " µs" << endl;

  return 0;
}
