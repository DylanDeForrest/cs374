#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    
    if (pid == 0) {
        execlp("ls", "ls", NULL);
    } else {
        printf("I am the parent process.\n");
        wait(NULL);
    }

    printf("we are done\n");
}