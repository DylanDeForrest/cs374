#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>  
#include <sys/types.h> 
  
#define DATA_SIZE 1024

int main(int argc, char *argv[]){

    if (argc < 4){
        perror("to few arguments\nusage: mmap_write int float string");
        exit(0);
    }

    int write_int = atoi(argv[1]);
    float write_flt = (float)atof(argv[2]);
    char *write_char = argv[3];

    int fd = open('data.dat', O_RDWR);
    void *data = mmap(NULL, DATA_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    void *p;



}