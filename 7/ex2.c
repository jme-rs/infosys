#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


void func1(int x);
void func2(int x);


int main(void) {
    pthread_t t1;
    pthread_t t2;
    printf("in main() pid = %d\n", getpid());
    pthread_create(&t1, NULL, (void *) func1, (void *) 10);
    pthread_create(&t2, NULL, (void *) func2, (void *) 20);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}


void func1(int x) {
    puts("thread_func1 called");
    printf("thread ID = %ld\n", pthread_self());
    printf("pid = %d\n", getpid());
    for (int i = 0; i < 3; i++) {
        printf("func1(%d): %d\n", x, i);
    }
}


void func2(int x) {
    puts("thread_func2 called");
    printf("thread ID = %ld\n", pthread_self());
    printf("pid = %d\n", getpid());
    for (int i = 0; i < 3; i++) {
        printf("func2(%d): %d\n", x, i);
    }
}