#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void do_child(int child_number) {
    printf("This is child %d (pid=%d).\n", child_number, getpid());
    exit(2);
}

int main() {
    pid_t child_pid, status;
    int   num_children = 1;

    for (int i = 1; i <= num_children; i++) {
        if ((child_pid = fork()) < 0) {
            perror("fork");
            exit(1);
        }

        if (child_pid == 0) {
            do_child(i);
        }
    }

    for (int i = 0; i < num_children; i++) {
        if (wait(&status) < 0) {
            perror("wait");
            exit(1);
        }
    }

    printf("This is parent(pid=%d).\n", getpid());
}
