#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF 256 

int main(int argc, char *argv[]){

    int buf[BUFF];

    mkfifo("myfifo", 0644);

    int fd = open("myfifo", O_RDONLY);

    while(1)
    {
        int n_bytes = read(fd, buf, sizeof(buf)-1);
        if (n_bytes == 0){
            break;
        }
        write(STDOUT_FILENO, buf, n_bytes);
    }
    close(fd);
}