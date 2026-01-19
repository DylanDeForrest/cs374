#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH 4096

long long calculate_size(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    struct stat statbuf;
    long long total = 0;
    char full_path[MAX_PATH];
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || 
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        snprintf(full_path, MAX_PATH, "%s/%s", path, entry->d_name);
        lstat(full_path, &statbuf);
        
        if (S_ISREG(statbuf.st_mode)) {
            total += statbuf.st_size;
        } else if (S_ISDIR(statbuf.st_mode)) {
            total += calculate_size(full_path);
        }
    }
    
    closedir(dir);
    printf("%s: %lld\n", path, total);
    
    return total;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "usage: filescanner [directory]\n");
        return 1;
    }
    
    calculate_size(argc == 2 ? argv[1] : ".");
    
    return 0;
}