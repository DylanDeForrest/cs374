#include <stdio.h>   // For perror()
#include <fcntl.h>   // For open()
#include <unistd.h>  // For write() and close()

int main(void){
    int fd;
    char buf[128];

    int bytes_read = read(0, buf, 128);
    
}