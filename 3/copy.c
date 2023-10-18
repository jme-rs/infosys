#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE *fp_orig;
    FILE *fp_dest;

    if (argc != 3) {
        puts("Usage: copy filename1 filename2");
        return 1;
    }

    fp_orig = fopen(argv[1], "r");
    if (!fp_orig) {
        puts("filename1: file not found");
        return 1;
    }

    fp_dest = fopen(argv[2], "w");
    if (!fp_dest) {
        puts("filename2: error opening file");
        return 1;
    }

    int word_state = 0;
    for (int ch = fgetc(fp_orig); ch != EOF; ch = fgetc(fp_orig)) {
        fputc(ch, fp_dest);
    }

    fclose(fp_orig);
    fclose(fp_dest);
    return 0;
}
