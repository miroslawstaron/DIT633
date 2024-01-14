/*
* This is an example of using _spawn function in Windows. 
* It is similar to the spawn function from POSIX, but it is a windows version
* A good reading about the spawn function can be found here: https://docs.microsoft.com/en-us/cpp/c-runtime-library/spawn-wspawn-functions?view=msvc-160 
*/

#include <stdio.h> 
#include <process.h> 

/*
* Demonstration of spawning the proces in windows
*/
int main_spawn(void)
{
    char* my_args[2];                   // array of argument to be sent to the program
                                        // in our case one, the array needs to end with NULL

    my_args[0] = "textfilename.txt";    // name of the file to open
    my_args[1] = NULL;                  // terminator of the argument list

    printf("%s\n", "Main: Spawning child with _spawnv"); 

    // creating the new process
    // and wait until it finishes
    _spawnv(P_NOWAIT,                           // wait for the program to finish, try _P_DETACH, _P_NOWAIT or _P_OVERLAY
            "c:/Windows/system32/notepad.exe",  // What we execute
            my_args);                           // argument list

    // writing that we end the process
    printf("%s\n", "Main: The end!");

    return 0;
}

