Lastly I began implementing part 3 by copying the buffer_user_sem.c to buffer_mon.c and just commented out everything semaphore related. I added a header file to make isFull(), isEmpty() and printLen(). I implemented those in their buffer_mon.c also and used printLen() in the enqueue and dequeue fxn. 

	Furthermore, I copied the test_sem.c to test_mon.c. However, I added the mutex lock and conditional variable to this file and initialized them in main. In the producer fxn I used a mutex lock to evaluate the conditional which waits on the lock to be free and the conditional to be false before reevaluating the while loop and enqueuing. After doing so, I broadcasted to all threads waiting on the conditional that it is no longer full or no longer empty and the corresponding producer and consumer thread will execute once acquiring the mutex which is released next.

	Moreover, I implemented the consumer thread by using the consumer thread from the previous part and just acquiring the mutex lock to evaluate if the buffer is empty. Once it is not empty and we have the lock we can dequeue, broadcast and release the lock.


