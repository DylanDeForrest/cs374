#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define MAX_RECORDS 1048576
#define RECORD_SIZE 32
#define HEADER_SIZE (sizeof(int) * 2)
#define FILE_SIZE (HEADER_SIZE + MAX_RECORDS * RECORD_SIZE)

void lock_region(int fd, off_t start, off_t len) {
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = start;
    fl.l_len = len;
    fcntl(fd, F_SETLKW, &fl);
}

void unlock_region(int fd, off_t start, off_t len) {
    struct flock fl;
    fl.l_type = F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = start;
    fl.l_len = len;
    fcntl(fd, F_SETLK, &fl);
}

void append_record(int fd, char *map, char *prefix, int serial) {
    int *header = (int *)map;

    lock_region(fd, 0, HEADER_SIZE);

    int offset = header[0];
    header[1] = header[1] + 1;
    header[0] = offset + RECORD_SIZE;

    unlock_region(fd, 0, HEADER_SIZE);

    char *record_ptr = map + HEADER_SIZE + offset;

    off_t record_start = HEADER_SIZE + offset;
    lock_region(fd, record_start, RECORD_SIZE);

    char buf[RECORD_SIZE];
    snprintf(buf, RECORD_SIZE, "%s %d", prefix, serial);
    memcpy(record_ptr, buf, RECORD_SIZE);

    unlock_region(fd, record_start, RECORD_SIZE);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: appendlog count prefix [count prefix ...]\n");
        return 1;
    }

    int fd = open("logfile.dat", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    ftruncate(fd, FILE_SIZE);

    char *map = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    int num_pairs = (argc - 1) / 2;
    int launched = 0;

    for (int i = 0; i < num_pairs; i++) {
        int count = atoi(argv[1 + i * 2]);
        char *prefix = argv[2 + i * 2];

        pid_t pid = fork();
        if (pid == 0) {
            for (int j = 0; j < count; j++) {
                append_record(fd, map, prefix, j);
            }
            munmap(map, FILE_SIZE);
            close(fd);
            exit(0);
        }
        launched++;
    }

    for (int i = 0; i < launched; i++) {
        wait(NULL);
    }

    int *header = (int *)map;

    lock_region(fd, 0, FILE_SIZE);

    int count = header[1];

    for (int i = 0; i < count; i++) {
        char *record = map + HEADER_SIZE + i * RECORD_SIZE;
        printf("%d: %s\n", i, record);
    }

    unlock_region(fd, 0, FILE_SIZE);

    munmap(map, FILE_SIZE);
    close(fd);

    return 0;
}