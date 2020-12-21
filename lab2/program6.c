/*
# Name: Andrew Knaus
# Date: 10/01/2020
# Title: Lab1 – task # Description: Task 6.  This program creates a Parent Thread
# and a Child Thread.  Each thread counts from 0 to 99.
*/

#include <stdio.h>      /* printf, stderr */
#include <stdlib.h>     /* atoi */
#include <unistd.h>     /* fork */
#include <pthread.h>    /* thread */

void *ThreadParentFun(void *argv) {
    int i;
    for (i=0;i<100;i++) {
        printf("\t \t \t Parent Thread %d \n",i);
        usleep((int) argv);
    }
    pthread_exit(NULL);
}

void *ThreadChildFun(void *argv) {
    int i;
    for (i=0;i<100;i++) {
        printf("Child Thread %d\n",i);
        usleep((int) argv);
    }
    pthread_exit(NULL);
}

/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t  pid;
    pthread_t threadParent, threadChild;
    int res;
    int n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before threading.\n");
    res = pthread_create(&threadParent, NULL, ThreadParentFun, (void *)(size_t) n); // creating parent thread
    if (res) {
        printf("Error:unable to create thread, %d\n", res);
        exit(-1);
    }
    res = pthread_create(&threadChild, NULL, ThreadChildFun, (void *)(size_t) n); //creating child thread
    if (res) {
        printf("Error:unable to create thread, %d\n", res);
        exit(-1);
    }
    pthread_exit(NULL);
}