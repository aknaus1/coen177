/*
# Name: Andrew Knaus
# Date: October 8th, 2020
# Title: Lab3 – step 6
# Description: Compile and run the following program, then list how many 
    threads are created and what values of i are passed?  Write down your 
    observation. You probably have seen that there is a bug in the program, 
    where threads may print same values of i. Why? 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {    
    int i;    
    for (i = 0; i < NTHREADS; i++){
        pthread_create(&threads[i], NULL, go, &i);
    }
    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), *(int *)arg);
    return 0;
}