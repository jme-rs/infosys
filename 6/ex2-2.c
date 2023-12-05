#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int  mygetcher(int time_out);
void _myGetchar(int time_out);
void timeout_handler();


int count_max;
int count = 0;
int c     = EOF;


int main() {
    int input = mygetcher(5);

    switch (input) {
        case -3:
            printf("error\n");
            break;

        case -2:
            printf("timeout\n");
            break;

        default:
            printf("input: %c\n", (char)input);
            break;
    }

    return 0;
}


int mygetcher(int time_out) {
    pid_t pid;
    int   status;

    switch (pid = fork()) {
        case -1:
            perror("fork");
            exit(1);

        case 0:
            _myGetchar(time_out);
            break;

        default:
            if (wait(&status) < 0) {
                perror("wait");
                exit(1);
            }
            else if (WIFEXITED(status)) {
                switch (WEXITSTATUS(status)) {
                    case 128:
                        return -3;

                    case 129:
                        return -2;

                    default:
                        return WEXITSTATUS(status);
                }
            }
            return status;
    }

    // don't reach here
    exit(0);
}


void _myGetchar(int time_out) {
    count_max = time_out;

    struct sigaction sa_alarm;
    struct itimerval itimer;

    memset(&sa_alarm, 0, sizeof(sa_alarm));
    sa_alarm.sa_handler = timeout_handler;
    sa_alarm.sa_flags   = SA_RESTART;

    if (sigaction(SIGALRM, &sa_alarm, NULL) < 0) {
        perror("sigaction");
        exit(128);
    }

    itimer.it_value.tv_sec = itimer.it_interval.tv_sec = 1;
    itimer.it_value.tv_usec = itimer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &itimer, NULL) < 0) {
        perror("setitimer");
        exit(128);
    }

    c = getchar();
    pause();
}


void timeout_handler() {
    count++;

    if (c != EOF) {
        exit(c);
    }

    if (count_max < count) {
        exit(129);
    }
}