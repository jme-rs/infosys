#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        puts("Usage: copy filename1 filename2");
        return 1;
    }

    int fd_orig = open(argv[1], O_RDONLY);
    if (fd_orig == -1) {
        puts("filename1: file not found");
        return 1;
    }

    int fd_dest = open(argv[2], O_WRONLY);
    if (fd_dest == -1) {
        puts("filename2: error opening file");
        close(fd_orig);
        return 1;
    }

    char buffer[64];
    ssize_t bytes_read;

    while ((bytes_read = read(fd_orig, buffer, sizeof(buffer))) > 0) {
        if (write(fd_dest, buffer, bytes_read) != bytes_read) {
            puts("Write error");
            close(fd_orig);
            close(fd_dest);
            return 1;
        }
    }

    close(fd_orig);
    close(fd_dest);
    return 0;
}
