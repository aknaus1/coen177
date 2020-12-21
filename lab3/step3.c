/*
# Name: Andrew Knaus
# Date: October 8th, 2020
# Title: Lab3 – step 3
# Description: Modify the program in Step 2. so that the writer process 
    passes the output of “ls” command to the upstream end of the pipe.  You 
    may use dup2(fds[1],1); for redirection, and execlp("ls", "ls", 0); to 
    run the “ls” command.#include <stdio.h>
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
// main
int main(int argc,char *argv[]){
    int  fds[2];
    char buff[100];
    int count;
    int i;
    pipe(fds);
    if (fork()==0){
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("ls", "ls", 0);
        exit(0);
    }
    else if(fork()==0){
        close(fds[1]);
        while((count=read(fds[0],buff,100))>0){
            for(i=0;i<count;i++){
                write(1,buff+i,1);
                write(1," ",1);
            }
            printf("\n");
        }
        exit(0);
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    } 
    return 0;
}