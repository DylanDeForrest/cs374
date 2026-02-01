#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


#define BUF_SIZE 256

int main(void){
    int fd = open("output.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644);

    dup2(fd, STDOUT_FILENO);

    close(fd);

    printf("Hello, world\nThis is a test!\n");

    fflush(stdout);
    
}

