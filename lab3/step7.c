/*
# Name: Andrew Knaus
# Date: October 8th, 2020
# Title: Lab3 – step 7
# Description: [Bonus] What is the fix for the program in Step 6, then 
    write a program to demonstrate your fix? STRUCTS YAY
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Iterator {
    int num;
} iterator;

void *go(void *);

#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {    
    int i;    
    for (i = 0; i < NTHREADS; i++){
        struct Iterator *x;
        x = malloc(sizeof(struct Iterator));
        (*x).num = i;
        pthread_create(&threads[i], NULL, go, (void *)x);
    }
    for (i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
    struct Iterator *x = (struct Iterator*)arg;
    printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), (*x).num);
    return 0;
}