#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void do_child() {
    printf("This is child(pid=%d).\n", getpid());
    exit(2);
}

int main() {
    pid_t child_pid, status;

    if ((child_pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        do_child();
    }
    else if (wait(&status) < 0) {
        perror("wait");
        exit(1);
    }

    printf("This is parent. The child (pid=%d) existed with status(%d).\n",
           child_pid,
           WIFEXITED(status));
}