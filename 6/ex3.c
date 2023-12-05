#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// Change this to change the number of lines to copy in the file.
#define LINE_NUM 100


void copy(int numRepetitions);
void print_lines();
void sigusr1_handler(int signum);


int main() {
    pid_t pid;
    signal(SIGUSR1, sigusr1_handler);

    switch (pid = fork()) {
        case -1:
            perror("fork");
            exit(1);

        case 0:
            copy(LINE_NUM);
            break;

        default:
            pause();
            print_lines();
            break;
    }

    return 0;
}


void copy(int numRepetitions) {
    FILE *fp;
    if ((fp = fopen("dst.txt", "w")) == NULL) {
        perror("fopen");
        exit(1);
    }

    for (int i = 0; i < numRepetitions; i++) {
        fprintf(fp, "Hello, world!\n");
    }

    fclose(fp);
    kill(getppid(), SIGUSR1);
    exit(0);
}


void print_lines() {
    FILE *fp;
    if ((fp = fopen("dst.txt", "r")) == NULL) {
        perror("fopen");
        exit(1);
    }

    int line = 0;
    for (char ch = fgetc(fp); ch != EOF; ch = fgetc(fp)) {
        if (ch == '\n') {
            line++;
        }
    }

    fclose(fp);
    printf("Number of lines: %d\n", line);
}


void sigusr1_handler(int signum) {
    printf("Child process finished.\n");
}