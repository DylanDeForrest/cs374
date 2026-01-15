#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <stdlib.h> 

int main(void){

    DIR *dr = opendir(".");
    struct dirent *de;

    while((de = readdir(dr)) != NULL){
        printf("%s\n", de->d_name);
    }

    closedir(dr);



}