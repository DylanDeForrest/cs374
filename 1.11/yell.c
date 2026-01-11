#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int fd, n;
    char buffer[2048];

    if (argc == 1) {
        while ((n = read(0, buffer, 2048)) > 0){
            for (int i = 0; i < n; i++)
                buffer[i] = toupper(buffer[i]);
            write(1, buffer, n);

        }
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        while ((n = read(fd, buffer, 2048)) > 0){
            for (int i = 0; i < n; i++)
                buffer[i] = toupper(buffer[i]);
            write(1, buffer, n);
        }
        close(fd);
    }

    return 0;
}