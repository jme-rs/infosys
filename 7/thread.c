/* create two threads */
#include <pthread.h>
#include <stdio.h> /* printf() */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void func1() {
    printf("thread ID = %ld\n", pthread_self());
}


int main(int argc, char *argv[]) {
    int num = atoi(argv[1]);
    printf("in main()\n");
    pthread_t t[num];

    for (int i = 0; i < num; ++i) 
        pthread_create(&t[i], NULL, (void *) func1, NULL);

    for (int i = 0; i < num; ++i)
        pthread_join(t[i], NULL);
}