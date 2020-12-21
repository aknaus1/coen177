/*
# Name: Andrew Knaus
# Date: 10/01/2020
# Title: Lab1 – task # Description: Task 1-4. This program creates a Parent Process
# and a Child Process.  Each process counts from 0 to 99.
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
    }
    if (pid) {        // Parent process
        for (i=0;i<100;i++) {
            printf("\t \t \t Parent Process %d \n",i);
            usleep(n);
        }
    } else {        // Child process
        for (i=0;i<100;i++) {
            printf("Child process %d\n",i);
            usleep(n);
        }
    }
    return 0;
}