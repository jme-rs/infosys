#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int num = atoi(argv[1]);
    printf("in main()\n");
    pid_t pid[num];

    for (int i = 0; i < num; ++i) {
        pid[i] = fork();
        switch (pid[i]) {
            case -1:
                perror("fork");
                exit(1);

            case 0:
                printf("child process ID = %d\n", getpid());
                exit(0);

            default:
                puts("parent");
                break;
        }
    }

    for (int i = 0; i < num; ++i) {
        int status;
        waitpid(pid[i], &status, 0);
    }
}