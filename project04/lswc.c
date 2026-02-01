#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    pid_t pid; 
    char *dic;
    int pfds[2];

    // set directory
    if (argc > 1) {
        dic = argv[1];
    }
    else {
        dic = ".";
    }
    
    // create pipe and fork
    pipe(pfds);
    pid = fork();

    int read_p = pfds[0];
    int write_p = pfds[1];
    
    if (pid == 0){
        // child  
        dup2(read_p, STDIN_FILENO);

        close(write_p);

        execlp("wc", "wc", "-l", NULL);

    }
    else {
        // parent
        dup2(write_p, STDOUT_FILENO);

        close(read_p);

        execlp("ls", "ls", "-1a", dic, NULL);


    }


}

