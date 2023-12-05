#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static volatile sig_atomic_t got_input = 0;

void timeout_handler() {
    got_input = 1;
}

int mygetchar(int timeout_seconds) {
    struct sigaction sa;
    sa.sa_handler = timeout_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGALRM, &sa, NULL);

    alarm(timeout_seconds); // タイムアウトまでの時間をセット

    int c;
    got_input = 0;

    while (!got_input) {
        printf("pause\n");
        pause(); // シグナルを待つ
    }

    alarm(0); // タイムアウトのリセット

    printf("getchar\n");
    c = getchar();

    if (c == EOF) {
        return -2; // EOFの場合
    } else {
        return c; // 入力された文字
    }
}

int main() {
    int input = mygetchar(5); // 5秒のタイムアウト

    if (input == -2) {
        printf("Timeout occurred.\n");
    } else {
        printf("Input character: %c\n", (char)input);
    }

    return 0;
}