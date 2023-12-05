#include <stdio.h>

extern char **environ;
int           data0;
int           data1 = 10;

main(int argc, char *argv[]) {
    char c;
    printf("environ:\t%0.8p\n", environ);
    printf("argv:\t\t%0.8p\n", argv);
    printf("stack:\t\t%0.8p\n", &c);
    printf("bss:\t\t%0.8p\n", &data0);
    printf("data:\t\t%0.8p\n", &data1);
}