/*
# Name: Andrew Knaus
# Date: October 26th, 2020
# Title: Lab 5 – step 2
# Description: Modify threadSync.c in Step1 using mutex Locks.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];

pthread_mutex_t lock; //Declare a lock

void* go(void* arg) { 
  pthread_mutex_lock(&lock); //lock acquire
  printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
  sleep(1); 
  pthread_mutex_unlock(&lock); //lock release
  return (NULL);
} 

int main() { 
   pthread_mutex_init(&lock, NULL); //Create a lock
   static int i;
   for (i = 0; i < NTHREADS; i++)  
      pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
   for (i = 0; i < NTHREADS; i++) {
      pthread_join(threads[i],NULL);
      printf("\t\t\tThread %d returned \n", i);
   }
   printf("Main thread done.\n");
   pthread_mutex_destroy(&lock); // delete lock
   return 0; 
} 
