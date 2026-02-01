#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if (argc < 3) {
        perror("usage: redirout filename command [arg1 [arg2 ... ] ]");
        exit(1);
    }

    int fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);

    dup2(fd, STDOUT_FILENO);

    close(fd);

    execvp(argv[2], argv +2);

}