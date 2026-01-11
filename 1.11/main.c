#include <stdio.h>

int main(){
    int x = 12;
    float y = 3.14;
    char* s = "Hello, World!";
    printf("x is %d, y is %f \n%s", x,y,s);
    for(int i = -1; i < 5; i++){
        int g = 5 * i;
        printf("%d x 5 = %d\n", i, g);
    }
}