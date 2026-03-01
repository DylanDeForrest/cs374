#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>


int main() {

    if (signal(SIGINT, SIG_IGN) == SIG_ERR){
        write(1, "Got SIGINT!\n", 12);
    }
    printf("Program will exit in 10 seconds. Hit ^C!");


    sleep(10);

}


