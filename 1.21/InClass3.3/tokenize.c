#include <stdio.h>
#include <string.h>

int main(void)
{
    char c[1024];

    while (1) {
    printf("prompt> "); fflush(stdout);
    fgets(c, sizeof c, stdin);

    char *token;
    int i = 0;

    if ((token = strtok(c, " ")) != NULL) do 
        puts(token);  // do something with the token
    while ((token = strtok(NULL, " ")) != NULL);
    }
    
}