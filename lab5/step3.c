/*
# Name: Andrew Knaus
# Date: October 26th, 2020
# Title: Lab 5 – step 3
# Description: Write a program that solves the producer - consumer problem using semaphores. You may use the following pseudo code for implementation.
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
#include <semaphore.h> 
#include <time.h>

#define NTHREADS 2

sem_t *empty;
sem_t *full;
int in = 0;
int out = 0;

pthread_mutex_t mutex; //Declare a lock

#define BUFFERSIZE 100
int buffer[BUFFERSIZE];

//Producer thread
void *producer(void *arg) {
    int item;
    while(1) {
        item = rand()%10;

        sem_wait(empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer Inserted Item %d at %d\n", buffer[in], in);
        in = (in+1)%BUFFERSIZE;
        sleep(1); 

        pthread_mutex_unlock(&mutex);
        sem_post(full);
    }
    return 0;
}

//Consumer thread
void *consumer(void *arg) {
    while(1) {
        sem_wait(full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer Removed Item %d from %d\n", item, out);
        out = (out+1)%BUFFERSIZE;
        sleep(1); 

        pthread_mutex_unlock(&mutex);
        sem_post(empty);
    }
    return 0;
}

int main() { 
    pthread_t threads[NTHREADS];
    full = sem_open("full_sem", O_CREAT, 0644, 0);
    empty = sem_open("empty_sem", O_CREAT, 0644, BUFFERSIZE);
    pthread_mutex_init(&mutex, NULL); //Create a lock

    pthread_create(&threads[0], NULL, producer, NULL);
    pthread_create(&threads[1], NULL, consumer, NULL);

    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
        printf("\t\t\tThread %d returned \n", i);
    }
    printf("Main thread done.\n");

    pthread_mutex_destroy(&mutex);
    sem_unlink("empty_sem"); 
    sem_unlink("full_sem"); 

    return 0; 
} 