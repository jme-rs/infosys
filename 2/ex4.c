#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#define LINE_LEN 64

int main() {
    char line_buf[LINE_LEN];
    char *line_ptr;

    while (fgets(line_buf, LINE_LEN, stdin) != NULL) {
        line_ptr = line_buf;
        size_t line_len = strlen(line_ptr);
        for (size_t i = 0; i < line_len; ++i) {
            if (isupper(line_ptr[i]))
                line_ptr[i] = tolower(line_ptr[i]);
            else if (islower(line_ptr[i]))
                line_ptr[i] = toupper(line_ptr[i]);
        }
        printf("%s\n", line_buf);
    }
}
