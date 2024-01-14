/*
* This file shows a simple file that shows how to use the semaphores on POSIX-based systems.
* 
* Comes from: https://www.geeksforgeeks.org/use-posix-semaphores-c/ 
* Use https://www.onlinegdb.com/ to execute the code
*/

#ifndef WIN32

#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 

// handle to the semaphore, just like the WIN32 example
sem_t mutex;

/*
* Worked function, which is executed in the thread. 
*/
void* thread(void* arg)
{
    // wait for the semaphore to open
    sem_wait(&mutex);

    printf("\nEntered..\n");

    //critical section 
    sleep(4);

    //signal 
    printf("\nJust Exiting...\n");
    
    // releasing the semaphore
    sem_post(&mutex);
}

/*
* Demonstration of the program using threads and semaphores
*/
int main()
{
    // create the semaphore
    sem_init(&mutex, 0, 1);

    // handle to two threads
    pthread_t t1, t2;

    // create threads
    pthread_create(&t1, NULL, thread, NULL);

    // waiting for two seconds
    sleep(2);

    // create another thread
    pthread_create(&t2, NULL, thread, NULL);

    // waiting for the threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // remove the semaphore
    sem_destroy(&mutex);

    // exit of the program
    return 0;
}

#endif // WIN32
