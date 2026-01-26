#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_SIZE 256

int main(void){

    char read_buf[128];
    int fd[2];
    pipe(fd);
    pid_t pid;
    pid = fork();

    if (pid == 0){
        close(fd[0]);
        const char *message =  "Hello, parent!\n";
        write(fd[1], message, strlen(message));
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    else {
        close(fd[1]);
        int n_bytes = read(fd[0], read_buf, sizeof(read_buf)-1);
        write(STDOUT_FILENO, read_buf, n_bytes);
        close(fd[0]);
        wait(NULL);
    }


}

