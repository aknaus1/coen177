/*
# Name: Andrew Knaus
# Date: October 8th, 2020
# Title: Lab3 – step 4
# Description: Write a C program to implement the producer-consumer message 
    communication using pipes. 

*/


#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

void producer(FILE *pipe_write_end)
{
  int i;
  for(i = 1; i <= 10; i++) {
    fprintf(pipe_write_end, "%d ", i);
    printf("producer wrote: %d\n", i);
  }
  fclose(pipe_write_end);
  exit(0);
}

void consumer(FILE *pipe_read_end)
{
  int n,k;

  while(1) {
    int n = fscanf(pipe_read_end, "%d", &k);
    if(n == 1) printf("consumer read: %d\n", k);
    else break;
  }
  fclose(pipe_read_end);
  exit(0);
}


// main
int main(int argc,char *argv[]){
    int  fds[2];
    FILE *pipe_write_end, *pipe_read_end;
    int i;
    pipe(fds);
    pipe_read_end  = fdopen(fds[0], "r");
    pipe_write_end = fdopen(fds[1], "w");
    if (fork()==0){
        close(fds[0]);
        producer(pipe_write_end);
    }
    else if(fork()==0){
        close(fds[1]);
        consumer(pipe_read_end);
    }
    else{
        fclose(pipe_read_end);
        fclose(pipe_write_end);
        wait(0);
        wait(0);
    }return 0;
}