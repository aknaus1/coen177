/*
# Name: Andrew Knaus
# Date: October 26th, 2020
# Title: Lab 5 – step 4
# Description: Write a program that solves the producer - consumer problem using condition variables. You may use the following pseudo code for implementation.
*/

//Shared data: semaphore full, empty, mutex;
//pool of n buffers, each can hold one item
//mutex provides mutual exclusion to the buffer pool
//empty and full count the number of empty and full buffers
//Initially: full = 0, empty = n, mutex = 1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h> 

#define NTHREADS 2

int in = 0;
int out = 0;
int occupied = 0;

pthread_mutex_t mutex; //Declare a lock
pthread_cond_t full, empty;

#define BUFFERSIZE 100
int buffer[BUFFERSIZE];

//Producer thread
void *producer(void *arg) {
    int item;
    while(1) {
        item = rand()%10;

        pthread_mutex_lock(&mutex);
        while(occupied >= BUFFERSIZE) {
            int x = pthread_cond_wait(&empty, &mutex);
            sleep(1); 
        }

        buffer[in] = item;
        printf("Producer Inserted Item %d at %d\n", buffer[in], in);
        in = (in+1)%BUFFERSIZE;
        occupied++;
        sleep(1);

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

//Consumer thread
void *consumer(void *arg) {
    int item;
    while(1) {
        pthread_mutex_lock(&mutex);
        while(occupied <= 0) {
            int x = pthread_cond_wait(&full, &mutex);
            sleep(1); 
        }

        item = buffer[out];
        printf("Consumer Removed Item %d from %d\n", item, out);
        out = (out+1)%BUFFERSIZE;
        occupied--;
        sleep(1); 

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

int main() { 
    pthread_t threads[NTHREADS];
    pthread_mutex_init(&mutex, NULL); //Create a lock
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    pthread_create(&threads[0], NULL, producer, NULL);
    pthread_create(&threads[1], NULL, consumer, NULL);

    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
        printf("\t\t\tThread %d returned \n", i);
    }
    printf("Main thread done.\n");

    pthread_mutex_destroy(&mutex);

    return 0; 
} 