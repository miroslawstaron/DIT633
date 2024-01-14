/*
* This is a demonstration program to show how threads and processes are handled in C
* This version is for the Windows 10, Visual Studio C compiler
* 
* In this program, we can see how to coordinate the threads using semaphores.
*/
#include <stdio.h>
#include <stdlib.h>
#include <process.h>        // this library is important as it containts threads and process handling
#include <windows.h>        // library that provides access to Win32 API, important for the threads management

// IMPORTANT - global variable for the semaphore
HANDLE ghSemaphore;


/*
* This function calculates the sum of numbers from 0 to iLastNumber
* @param args -- here we use an array
* return: the sum or 0 if the number is too large
*/
void calculate_sum_sem(int* args)
{
    unsigned long iSum = 0;         // declare the result
    int i = 0;                      // loop index

    DWORD dwWaitResult;             // 

    // unpacking the arguments to variables
    int iLastNumber = args[0];
    int iThreadID = args[1];   
    
    dwWaitResult = WaitForSingleObject(
        ghSemaphore,   // handle to semaphore
        10L);           // zero-second time-out interval

    switch (dwWaitResult)
    {
        case WAIT_OBJECT_0:
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

            if (!ReleaseSemaphore(
                ghSemaphore,  // handle to semaphore
                1,            // increase count by one
                NULL));       // not interested in previous count
            break;

        case WAIT_TIMEOUT:
            printf("Thread %d: wait timed out\n", GetCurrentThreadId());
            break;
    }
    // windows library function needed for the thread to end correctly
    _endthread();
}

/*
* Function which demonstrates the basics of threads in Windows
*/
int basics_sem_main()
{
    printf("%s", "Starting main... \n");

    // Create a semaphore
    // using the WIN32 API
    ghSemaphore = CreateSemaphore(
        NULL,           // default security attributes
        1,              // initial count of semaphores
        1,              // maximum count of semaphores
        NULL);          // unnamed semaphore

    // Failsafety -- if the semaphore is not created
    if (ghSemaphore == NULL)
    {
        // if the semephore was not created, we leave
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }


    // four threads, four handles
    HANDLE  hThread1,
            hThread2,
            hThread3,
            hThread4;

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

    // we create four threads and start them
    hThread1 = _beginthread(calculate_sum_sem, 10, arg[0]);
    hThread2 = _beginthread(calculate_sum_sem, 10, arg[1]);
    hThread3 = _beginthread(calculate_sum_sem, 10, arg[2]);
    hThread4 = _beginthread(calculate_sum_sem, 10, arg[3]);

    // write that we are in main
    printf("%s", "In main, taking a nap... \n");

    // we do some sleep to see what happens
    Sleep(10000);

    // write that we are in main
    printf("%s", "In main, finished my nap... \n");

    // and we wait for the threads to finish
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);
    WaitForSingleObject(hThread4, INFINITE);

    // Close the semaphore
    CloseHandle(ghSemaphore);

    // and that's it
    printf("%s", "Main ends! \n");

    return 0;
}
