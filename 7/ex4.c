#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int shared_resource;


void func1();
void func2();


int main(void) {
    pthread_t t1;
    pthread_t t2;
    shared_resource = 0;

    pthread_create(&t1, NULL, (void *) func1, NULL);
    pthread_create(&t2, NULL, (void *) func2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("main(): shared_resource == %d\n", shared_resource);
}


void func1() {
    for (int i = 0; i < 1000000; i++) {
        shared_resource++;
    }
}


void func2() {
    for (int i = 0; i < 1000000; i++) {
        shared_resource++;
    }
}