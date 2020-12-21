/*
# Name: Andrew Knaus
# Date: October 15th, 2020
# Title: Lab3 – step 3
# Description: Write a program that uses threads to perform a parallel matrix multiply.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NTHREADS 2
#define N 2
#define M 3
#define L 3

int matrixA[N][M], matrixB[M][L], matrixC[N][L];

//Declares threads
pthread_t threads[NTHREADS];

//Holds i value
typedef struct {
    int num;
}Holder;

void *multi(void *arg) {
    Holder *x = (Holder*)arg;
    for (int i = 0; i < M; i++)  
        for (int j = 0; j < L; j++)  
            matrixC[(*x).num][j] += matrixA[(*x).num][i] * matrixB[i][j]; 
    return NULL;
}

int main() {
    srand(time(NULL));

    //Randomly filling Matrix A
    printf("---Matrix A---\n");
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < M; j++) { 
            matrixA[i][j] = rand()%10; 
            printf("%d ", matrixA[i][j]); 
        } 
        printf("\n");
    }

    //Randomly fillinng Matrix B
    printf("---Matrix B---\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < L; j++) {
            matrixB[i][j] = rand()%10;
            printf("%d ", matrixB[i][j]); 
        }
        printf("\n");
    }

    //Creating threads
    for (int i = 0; i < NTHREADS; i++) {
        Holder *x;
        x = malloc(sizeof(Holder));
        (*x).num = i;
        pthread_create(&threads[i], NULL, multi, (void *)x); 
    }

    //Waiting for threads to complete
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);   
    }

    //Printing Result Matrix C
    printf("---Matrix C---\n");
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < L; j++)  
            printf("%d ", matrixC[i][j]); 
        printf("\n");
    }
}
