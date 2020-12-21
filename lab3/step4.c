/*
# Name: Andrew Knaus
# Date: October 8th, 2020
# Title: Lab3 – step 4
# Description: Write a C program that implements the shell command:  
    cat /  etc/passwd | grep root
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// main
int main(int argc,char *argv[]){
    int  fds[2];
    pipe(fds);
    if (fork()==0){
        dup2(fds[1], 1);
        close(fds[0]);
        execlp("cat", "cat", "/etc/passwd", (char *) 0);
        exit(0);
    }
    else if(fork()==0){
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("grep", "grep", "root", (char *) 0);
        exit(0);
    }
    else{
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }return 0;
}