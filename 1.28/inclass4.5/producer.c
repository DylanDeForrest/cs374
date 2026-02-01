#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    char buf[16];
    int count = atoi(argv[1]);
    
    mkfifo("myfifo", 0644);

    int fd = open("myfifo", O_WRONLY);

    for(int i = 0; i < count; i++){
        buf[0] = i;
        sprintf(buf+1, "Message #%d", i);
        write(fd, buf, 16);
        sleep(1);
    }

    close(fd);

    exit(0);
}