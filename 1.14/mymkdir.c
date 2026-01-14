#include <stdio.h>
#include <errno.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <stdlib.h> 

int main(int argc, char *argv[]){
    if (argc != 2) {
        perror("too manny argumenets");
        return 1;
    }

    int check = mkdir(argv[1], 0700);

    if (!check) {
        return 1;
    }
    else {
        perror(argv[1]);
    }

    return 0; 
}