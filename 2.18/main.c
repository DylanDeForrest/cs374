#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_routine(void *arg){
    int thread_num = *((int *)arg);
    printf("thread %d: running\n");
    pthread_exit(NULL);
}

int main(){
    for (i=0; i < 3; i++){
        rc = 
    }
}