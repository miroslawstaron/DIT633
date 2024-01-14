/*
* This file contains an example of an algorithm demonstrating semaphores. 
* It is taken directly from the MS Visual Studio documentation: https://docs.microsoft.com/en-us/windows/win32/sync/using-semaphore-objects
*/

// Libraries for handling processes and IO
#include <windows.h>
#include <process.h>
#include <stdio.h>

#define MAX_SEM_COUNT 1        // The number of semaphores to create
#define THREADCOUNT 30          // The number of threads to coordinate

HANDLE ghSemaphore;             // Global handle to semaphores

/*
* An example function for making some calculations. 
* In the example from visual studio, this function just waits (sleep).
*/
DWORD WINAPI ThreadProc(LPVOID);

/*
* Function demonstrating the creation of threads and semaphores
*/
int main_sem(void)
{
    HANDLE aThread[THREADCOUNT];        // array of thread handles
    DWORD ThreadID;                     // ID of the thread that is created in the for loop                       

    // Create a semaphore with initial and max counts of MAX_SEM_COUNT
    ghSemaphore = CreateSemaphore(
        NULL,           // default security attributes
        MAX_SEM_COUNT,  // initial count
        MAX_SEM_COUNT,  // maximum count
        NULL);          // unnamed semaphore

    // failsafety - if the semaphore is not created, then we do not run any threads
    if (ghSemaphore == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    // Create worker threads
    for (int i = 0; i < THREADCOUNT; i++)
    {
        aThread[i] = CreateThread(
            NULL,       // default security attributes
            0,          // default stack size
            (LPTHREAD_START_ROUTINE)ThreadProc,
            NULL,       // no thread function arguments
            0,          // default creation flags
            &ThreadID); // receive thread identifier

        if (aThread[i] == NULL)
        {
            printf("CreateThread error: %d\n", GetLastError());
            return 1;
        }
    }

    // Wait for all threads to terminate
    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

    // Close thread handles
    for (int i = 0; i < THREADCOUNT; i++)
        CloseHandle(aThread[i]);

    // close the semaphore handle
    CloseHandle(ghSemaphore);

    return 0;
}

/*
* Demonstration of a thread function
* @param lpParam -- list of parameters, LPVOID is a typdef for void *
* @return -- thread exit code, DWORD is a typedef for unsigned long
*/
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    // lpParam not used in this example
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;             // result of waiting for the semaphore -- either opened or waiting (closed)
    BOOL bContinue = TRUE;          // bool variable for the loop where we check the value of the semaphore

    while (bContinue)
    {
        // Try to enter the semaphore 
        dwWaitResult = WaitForSingleObject(
            ghSemaphore,   // handle to semaphore
            10L);           // zero-second time-out interval

        switch (dwWaitResult)
        {
            // The semaphore object was signaled
            // i.e. open - we can enter this section
            case WAIT_OBJECT_0:
                // just a simple code here
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                bContinue = FALSE;

                // Simulate thread spending time on task
                Sleep(1000);

                
                // Release the semaphore when task is finished
                // this is important, otherwise it will lead to a deadlock
                if (!ReleaseSemaphore(
                    ghSemaphore,    // handle to semaphore
                    1,              // increase count by one
                    NULL))          // not interested in previous count
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            // The semaphore was nonsignaled, so a time-out occurred
            // this is important as we want to avoid deadlocks
            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}