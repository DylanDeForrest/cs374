#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


int main(int argc, char *argv[]){
  struct stat st;

  stat(argv[0], &st);
  printf("File size: %d bytes\n", st.st_size);

  return 0;
}