/*
# Name: Andrew Knaus
# Date: 10/01/2020
# Title: Lab1 – task # Description: Task 5.  This program creates seven Processes
# including the Parent Processes.  Each process counts from 0 to 7.
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */

/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t  pid, pidb, pidc, pidd;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
    if (pid) {
        pidb = fork ();
        if (pidb == -1) {
            fprintf(stderr, "can't fork, error %d\n", errno);
        }
        if(pidb) {
            printf("Parent Process %d, Parent Pid: %d, Pid: %d\n", i, getppid(), getpid());  // Parent/Parent/Parent
            usleep(n);

        } else {
            pidc = fork ();
            if (pidc == -1) {
                fprintf(stderr, "can't fork, error %d\n", errno);
            }
            if(pidc) {
                pidd = fork ();
                if (pidd == -1) {
                    fprintf(stderr, "can't fork, error %d\n", errno);
                }
                if(pidd) {
                    printf("Child #1 process %d, Parent Pid: %d, Pid: %d\n", i, getppid(), getpid()); // Parent/Child/Parent *child ***parent
                    usleep(n);
                } else {
                    printf("Child #2 process %d, Parent Pid: %d, Pid: %d\n", i, getppid(), getpid());  // Parent/Child/Child ***child
                    usleep(n);
                }
            } else {
                printf("Child #3 process %d, Parent Pid: %d, Pid: %d\n", i, getppid(), getpid());  // Parent/Child/Child ***child
                usleep(n);
            }
        }
    } else {
        pidb = fork ();
        if (pidb == -1) {
            fprintf(stderr, "can't fork, error %d\n", errno);
        }
        if(pidb) {
            pidc = fork ();
            if (pidc == -1) {
                fprintf(stderr, "can't fork, error %d\n", errno);
            }
            if(pidc) {
                printf("Child #4 process %d, Parent Pid: %d, Pid: %d\n", i, getppid(), getpid()); // Child/Parent/Parent
                usleep(n);
            } else {
                printf("Child #5 process %d, Parent Pid: %d, Pid: %d\n", i, getppid(), getpid());  // Child/Parent/Child
                usleep(n);
            }
        } else {

            printf("Child #6 process %d, Parent Pid: %d, Pid: %d\n", i, getppid(), getpid()); // Child/Child/Parent **parent
            usleep(n);
        }
    }
    return 0;
}