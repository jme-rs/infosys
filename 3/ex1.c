#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int   char_count = 0;
    int   line_count = 1;

    int word_count = 0;

    if (argc != 2) {
        puts("Usage: ex1 filename");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (!fp) {
        puts("file not found");
        return 1;
    }

    int word_state = 0;
    for (int ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {
        ++char_count;
        if (ch == '\n')
            ++line_count;

        if (isalpha(ch) && !word_state) {
            ++word_count;
            word_state = 1;
        }
        else if (!isalpha(ch)) {
            word_state = 0;
        }
    }

    printf("Characters: %d\n", char_count);
    printf("Lines     : %d\n", line_count);
    printf("Words     : %d\n", word_count);

    fclose(fp);
    return 0;
}
