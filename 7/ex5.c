#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


void func1();
void func2();


int             shared_resource;
pthread_mutex_t mutex;


int main(void) {
    pthread_t t1;
    pthread_t t2;
    shared_resource = 0;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, (void *) func1, NULL);
    pthread_create(&t2, NULL, (void *) func2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("main(): shared_resource == %d\n", shared_resource);
}


void func1() {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        shared_resource++;
        pthread_mutex_unlock(&mutex);
    }
}


void func2() {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        shared_resource++;
        pthread_mutex_unlock(&mutex);
    }
}