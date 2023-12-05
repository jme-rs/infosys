#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

void do_child() {
    char *argv[3];
    printf("This is child(pid=%d).\n", getpid());

    // argv[0] = "/bin/ls";
    // argv[1] = "/";
    // argv[2] = NULL;
    // execve(argv[0], argv, environ);
    execlp("free", "free", NULL, NULL);
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