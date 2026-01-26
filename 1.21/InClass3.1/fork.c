#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    
    if (pid == 0) {
        printf("I am the child process.\n");
    } else {
        wait(NULL);
        printf("I am the parent process.\n");
    }

    printf("we are done\n");
}