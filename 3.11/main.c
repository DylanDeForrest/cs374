#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void f1(void){
    puts("f1 called");
}

void f2(void){
    puts("f2 called");
}

void main(void){

    void (*runf[])(void) = {
        f1,
        f2,
        f1,
        f1,
        f2,
        NULL
    };

    for (int i = 0; runf[i] != NULL; i++){
        runf[i]();
    }
    puts("done");
}