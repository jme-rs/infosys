#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// The execution number of cp and ls
#define N 5

void check_args(int argc, char *argv[]); // Check the arguments
void child_cp(char *src);                // Copy the file
void child_ls();                         // Print the file list
void cleanup();                          // Cleanup the files

// Main
int main(int argc, char *argv[]) {
    pid_t cp_pid, ls_pid;
    pid_t status;

    check_args(argc, argv); // Check the arguments

    cleanup(); // Cleanup the files

    // Fork cp
    if ((cp_pid = fork()) == 0) {
        child_cp(argv[1]);
        exit(0);
    }
    else if (cp_pid < 0) {
        perror("fork cp");
        exit(1);
    }

    // Fork ls
    if ((ls_pid = fork()) == 0) {
        child_ls();
        exit(0);
    }
    else if (ls_pid < 0) {
        perror("fork ls");
        exit(1);
    }

    // Wait for cp and ls
    for (int i = 0; i < 2; ++i) {
        if (wait(&status) < 0) {
            perror("wait");
            exit(1);
        }
    }

    return 0;
}

void check_args(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./Exec6 <file>\n");
        exit(1);
    }

    FILE *fp;
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "File not found.\n");
        exit(1);
    }
    fclose(fp);
}

void child_cp(char *src) {
    char dst[32];
    for (int i = 0; i < N; ++i) {
        pid_t cp_pid, status;

        sprintf(dst, "dest_%d.txt", i);
        if ((cp_pid = fork()) == 0) {
            execlp("cp", "cp", src, dst, NULL);
        }
        else if (cp_pid < 0) {
            perror("fork cp");
            exit(1);
        }

        if (wait(&status) < 0) {
            perror("wait");
            exit(1);
        }

        sleep(1);
    }
}

void child_ls() {
    for (int i = 0; i < N; ++i) {
        pid_t ls_pid, status;

        if ((ls_pid = fork()) == 0) {
            execlp("ls", "ls", "-l", NULL);
        }
        else if (ls_pid < 0) {
            perror("fork ls");
            exit(1);
        }

        if (wait(&status) < 0) {
            perror("wait");
            exit(1);
        }

        sleep(1);
    }
}

void cleanup() {
    for (int i = 0; i < N; ++i) {
        char dst[32];
        sprintf(dst, "dest_%d.txt", i);
        remove(dst);
    }
}
