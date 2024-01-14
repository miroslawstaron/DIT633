/*
* This is a demonstration program to show how threads and processes are handled in C
* This version is for the Windows 10, Visual Studio C compiler
*/
#include <stdio.h>
#include <stdlib.h>
#include <process.h>        // this library is important as it containts threads and process handling
#include <windows.h>        // library that provides access to Win32 API, important for the threads management

/*
* This function calculates the sum of numbers from 0 to iLastNumber
* @param args -- here we use an array
* return: the sum or 0 if the number is too large
*/
void calculate_sum(int* args)
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
        args[2] = iSum;
    }

    Sleep(1000);

    // notify the we have reached the end
    printf("%s, ID %d, result: %ld\n", "Thread function ends", iThreadID, iSum);

    // windows library function needed for the thread to end correctly
    _endthread();
}

/*
* Function which demonstrates the basics of threads in Windows
*/
void basics_main()
{
    printf("%s", "Starting main... \n");

    // four threads, four handles
    HANDLE  hThread1,
        hThread2,
        hThread3,
        hThread4;

    int arg[4][3];      // arguments to the functions

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
    hThread1 = _beginthread(calculate_sum, 10, arg[0]);
    hThread2 = _beginthread(calculate_sum, 10, arg[1]);
    hThread3 = _beginthread(calculate_sum, 10, arg[2]);
    hThread4 = _beginthread(calculate_sum, 10, arg[3]);

    printf("Handler 1: %x\n", hThread1);

    // write that we are in main
    printf("%s", "In main, taking a nap... \n");

    // we do some sleep to see what happens
    // Sleep(10);

    // write that we are in main
    printf("%s", "In main, finished my nap... \n");

    // and we wait for the threads to finish
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
    WaitForSingleObject(hThread3, INFINITE);
    WaitForSingleObject(hThread4, INFINITE);

	printf("From Thread 1: %d\n", arg[0][2]);
	printf("From Thread 2: %d\n", arg[1][2]);
	printf("From Thread 3: %d\n", arg[2][2]);
	printf("From Thread 4: %d\n", arg[3][2]);
    
    
    
    // and that's it
    printf("%s", "Main ends! \n");
}
