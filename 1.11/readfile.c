#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd;
    char buffer[2048];
    int n;

    fd = open(argv[1], O_RDONLY);
    n = read(fd, buffer, 2048);
    write(1, buffer, n);
    close(fd);

    return 0;

}