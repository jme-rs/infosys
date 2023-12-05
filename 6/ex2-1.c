#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define PROGRESS_BAR_WIDTH 10

int progress;


void progress_bar() {
    printf("#");
    fflush(stdout);
}


int main() {
    struct sigaction sa_alarm;
    struct itimerval itimer;

    memset(&sa_alarm, 0, sizeof(sa_alarm));
    sa_alarm.sa_handler = progress_bar;
    sa_alarm.sa_flags   = SA_RESTART;

    if (sigaction(SIGALRM, &sa_alarm, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    itimer.it_value.tv_sec = itimer.it_interval.tv_sec = 1;
    itimer.it_value.tv_usec = itimer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &itimer, NULL) < 0) {
        perror("setitimer");
        exit(1);
    }

    for (progress = 0; progress < PROGRESS_BAR_WIDTH; progress++) {
        pause();
        // printf("main: %ld\n", time(NULL));
    }
    printf("\n");
}