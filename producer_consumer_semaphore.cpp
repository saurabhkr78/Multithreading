#include <bits/stdc++.h>
#include <semaphore>  // Required for std::binary_semaphore
using namespace std;

std::binary_semaphore signal_to_producer{1}, signal_to_consumer{0};

#define buff_size 5  // Fixed define syntax
int buff[buff_size]; // Fixed incorrect array declaration

void producer() {
    while (true) {
        signal_to_producer.acquire();
        cout << "Produced = ";
        for (int i = 0; i < buff_size; i++) {
            buff[i] = i * i;
            std::cout << buff[i] << " " << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        cout << endl;
        signal_to_consumer.release();
    }
}

void consumer() {
    while (true) {
        signal_to_consumer.acquire();
        cout << "Consumed = ";
        for (int i = buff_size - 1; i >= 0; i--) {
            std::cout << buff[i] << " " << std::flush;
            buff[i] = 0; // Task for consumer
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        cout << endl;
        signal_to_producer.release();
    }
}

int main() {
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);

    std::cout << "Main thread got the signal\n";

    producer_thread.join();
    consumer_thread.join();

    return 0;
}
