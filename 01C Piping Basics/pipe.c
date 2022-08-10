#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGSIZE 512;


int main(void) {

    char inbuf[MSGSIZE];
    int fd[2], j;
    pid_t pid;


    if (pipe(fd) == -1) {
        perror("pipe call");
        exit(1);
    }

    pid = fork();
    
    if (pid < 0) { 
        printf(stderr, "Fork Failed"); //error
        return 1;
    }
    else if (pid == 1) {
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        exe("./pre");
    }
    else {
        exe("./sort");
        exit(0);
    }

    return(1);
}
