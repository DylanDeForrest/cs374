#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <stdlib.h> 

#define MAX_PATH 4096

int main(void){

    DIR *dr = opendir(".");
    struct dirent *de;
    char fullpath[1024]

    while((de = readdir(dr)) != NULL){
        printf("%s\n", de->d_name);
    }

    closedir(dr);



}