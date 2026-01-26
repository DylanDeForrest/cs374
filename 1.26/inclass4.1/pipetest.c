#include <unistd.h>

#define BUF_SIZE 100

int main(void){

    char buf[128];

    int pfds[2];

    pipe(pfds);

    int read_fd = pfds[0];
    int write_fd = pfds[1];



    write(write_fd, "hello\n", 6 );
    int count = read(read_fd, buf, sizeof buf);

    write(1, buf, count);

}

