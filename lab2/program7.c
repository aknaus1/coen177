/*
# Name: Andrew Knaus
# Date: 10/01/2020
# Title: Lab1 – task # Description: Task 7.  This program creates a Parent Process
# and a Child Process.  The Parent Process waits for the child process the 
# finish before exiting.  The Child Process returns the list of files in
# the current directory.
*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */

/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t  pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\nBefore forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    } else if (pid) {        // Parent process
        for (i=0;i<100;i++) {
            printf("\t \t \t Parent Process %d \n",i);
            usleep(n);
        }
        wait(NULL);
        printf("Child Complete\n");
        exit(0);
    } else {        // Child process
        for (i=0;i<100;i++) {
            printf("Child process %d\n",i);
            usleep(n);
        }
        execlp("/bin/ls", "ls", NULL);
    }
    return 0;
}