#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Check if the arguments are correct
// Return
//   0: incorrect
//   1: correct
int is_correct_args(int argc, char *argv[]);

// Copy the contents of filename1 to filename2
// Return
//   0: success
//   1: filename1 not found
//   2: cannot make filename2
//   3: cannot write to filename2
int copy(char *filename1, char *filename2);

int main(int argc, char *argv[]) {
    if (!is_correct_args(argc, argv))
        exit(1);

    if (copy(argv[1], argv[2]))
        exit(1);

    puts("Copy successful");
    return 0;
}

int is_correct_args(int argc, char *argv[]) {
    if (argc != 3) {
        puts("Usage: copy filename1 filename2");
        return 0;
    }
    else if (strcmp(argv[1], argv[2]) == 0) {
        puts("Error: filename1 and filename2 are the same");
        return 0;
    }
    return 1;
}

int copy(char *filename1, char *filename2) {
    int fd_orig = open(filename1, O_RDONLY);
    if (fd_orig == -1) {
        puts("Error: file not found in filename1");
        return 1;
    }

    int fd_dest = open(filename2,
                       O_WRONLY | O_CREAT | O_TRUNC,
                       S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (fd_dest == -1) {
        puts("Error: cannot make file in filename2");
        close(fd_orig);
        return 2;
    }

    // Change buffer size here /////
    char buffer[1024];
    ////////////////////////////////
    ssize_t rcount;
    ssize_t wcount;

    while ((rcount = read(fd_orig, buffer, sizeof(buffer))) > 0) {
        wcount = write(fd_dest, buffer, rcount);
        if (wcount != rcount) {
            puts("Error: cannot write to filename2");
            close(fd_orig);
            close(fd_dest);
            return 3;
        }
    }

    close(fd_orig);
    close(fd_dest);
    return 0;
}
