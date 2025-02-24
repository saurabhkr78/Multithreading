/*both helps in sync in thoer own way

mutex:allows only one thread to go into critical section at a time
semaphore:allows n threads to go into critical section at a time like a resource is divided into n parts and n threads can access it at a time
mutex: it only have two states locked and unlocked
semaphore: it cann have only limited numbers of thread to access the resources at a time to maintain the thread it uses counter
mutex:locking mechanism
semaphore:signalling mechanism


working of semaphore:
suppose we have a semaphore with 3 resources and 5 threads
1st thread will access the resource and semaphore will decrease the counter to 2
2nd thread will access the resource and semaphore will decrease the counter to 1
3rd thread will access the resource and semaphore will decrease the counter to 0
4th thread will wait for the semaphore to increase the counter
5th thread will wait for the semaphore to increase the counter
when 1st thread will release the resource semaphore will increase the counter to 1 and 4th thread will access the resource
when 2nd thread will release the resource semaphore will increase the counter to 2 and 5th thread will access the resource
when 3rd thread will release the resource semaphore will increase the counter to 3 and 4th thread will access the resource
when 4th thread will release the resource semaphore will increase the counter to 4 and 5th thread will access the resource
when 5th thread will release the resource semaphore will increase the counter to 5 and no thread will wait for the resource

*/



