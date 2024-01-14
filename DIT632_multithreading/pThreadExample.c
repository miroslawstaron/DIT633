/*
* This file is an example of the code for the pthread.h library.
* It does not work on Windows, but it does work on the linux machines.
* It also works on Cygwin, but requires some effort to set-up
*
* works very well under https://www.onlinegdb.com/
*/

#ifndef WIN32

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/*
* This function calculates the sum of numbers from 0 to iLastNumber
* @param args -- here we use an array
* return: the sum or 0 if the number is too large
*/
void* calculate_sum(int* args)
{
    unsigned long iSum = 0;         // declare the result
    int i = 0;                      // loop index

    // unpacking the arguments to variables
    int iLastNumber = args[0];
    int iThreadID = args[1];

    // print information about the thread
    printf("%s, ID: %d\n", "Thread function starts", iThreadID);

    // loop to calculate the sum
    // until the overflow
    for (i = 0; i < iLastNumber; i++)
    {
        // condition to check if we go above the limit of unsigned long
        // simply we check if the next number will be smaller, then this means
        // that we have reached the limit
        if (iSum > iSum + 1)
        {
            iSum = 0;
            break;
        }

        // if not, then we add to the sum
        iSum += i;
    }

    // notify the we have reached the end
    printf("%s, ID %d, result: %ld\n", "Thread function ends", iThreadID, iSum);

    // windows library function needed for the thread to end correctly

}

int main()
{

    printf("%s", "Starting main... \n");

    int arg[4][2];      // arguments to the functions

    // the first thread
    arg[0][0] = 10;
    arg[0][1] = 1;

    // the second thread
    arg[1][0] = 20;
    arg[1][1] = 2;

    // the third thread
    arg[2][0] = 200;
    arg[2][1] = 3;

    // the fourth thread
    arg[3][0] = 100;
    arg[3][1] = 4;

    // four threads, four handles
    pthread_t ptrThread0,
        ptrThread1,
        ptrThread2,
        ptrThread3;

    // we create four threads and start them
    pthread_create(&ptrThread0, NULL, calculate_sum, &arg[0]);
    pthread_create(&ptrThread1, NULL, calculate_sum, &arg[1]);
    pthread_create(&ptrThread2, NULL, calculate_sum, &arg[2]);
    pthread_create(&ptrThread3, NULL, calculate_sum, &arg[3]);

    // write that we are in main
    printf("%s", "In main, taking a nap... \n");

    // we do some sleep to see what happens
    sleep(10000);

    // write that we are in main
    printf("%s", "In main, finished my nap... \n");

    // and we wait for the threads to finish
    pthread_join(ptrThread0, NULL);
    pthread_join(ptrThread1, NULL);
    pthread_join(ptrThread2, NULL);
    pthread_join(ptrThread3, NULL);

    // and that's it
    printf("%s", "Main ends! \n");

    return 0;

}

#endif