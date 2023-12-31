#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    FILE *fp_orig;
    FILE *fp_dest;

    fp_orig = fopen(filename1, "r");
    if (!fp_orig) {
        puts("Error: file not found in filename1");
        return 1;
    }

    fp_dest = fopen(filename2, "w");
    if (!fp_dest) {
        puts("Error: cannot make file in filename2");
        return 2;
    }

    for (int ch = fgetc(fp_orig); ch != EOF; ch = fgetc(fp_orig))
        fputc(ch, fp_dest);

    fclose(fp_orig);
    fclose(fp_dest);
    return 0;
}
