#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>


void progress_bar() {
    printf("progress_bar: %ld\n", time(NULL));
}


int main() {
    struct sigaction sa_alarm;
    struct itimerval itimer;
    int              counter = 10;

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

    while (counter--) {
        pause();
        printf("main: %ld\n", time(NULL));
    }
}