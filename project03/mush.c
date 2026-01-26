#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 2048
#define MAX_ARGS 128


void run_command(char *argv[]){
    pid_t pid = fork();

    if (pid < 0){
        perror("fork");
        return;
    }

    if (pid == 0){
        execvp(argv[0], argv);
        perror(argv[0]);
        exit(1);
    }else {
        wait(NULL);
    }
}

int main(void)
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1) {
        printf("mush$ "); 
        fflush(stdout);
        if(fgets(line, MAX_LINE, stdin)==NULL){
            continue;
        }

        int i = 0;
        args[i] = strtok(line, " \t\n");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " \t\n");
        }
        args[i] = NULL;

        if (args[0] == NULL){
            continue;
        }

        if (strcmp(args[0], "exit") == 0){
            exit(0);
        }

        if (strcmp(args[0], "cd") == 0){
            if (args[1] != NULL){
                chdir(args[1]);
            }
            continue; 
        }
        run_command(args);
    }
}