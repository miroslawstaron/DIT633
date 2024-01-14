/*
* This is an example of handling processes in POSIX, will work only on Linux/Unix/MacOS systems
* Paste it to https://www.onlinegdb.com/
*/

#ifndef WIN32

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(void) {

    // process id of the child process
    pid_t child;

    // forking, creating a new process
    if ((child = fork()) < 0) {
        printf("Problem with fork()\n");
        exit(1);
    }
    // here we check if we are in the parent or child process
    else if (child == 0) {
        printf("In child process, parent ID %d\n", getppid());
        printf("In child process, process ID %d\n", getpid());
    }
    else {
        printf("In parent process, process ID %d\n", getpid());
    }

    return 0;

}

#endif