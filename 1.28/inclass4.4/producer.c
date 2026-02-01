#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    mkfifo("myfifo", 0644);

    int fd = open("myfifo", O_WRONLY);

    write(fd, argv[1], strlen(argv[1]) + 1);

    close(fd);

    exit(0);
}