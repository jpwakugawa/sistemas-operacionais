#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int var;

void* thread1(void* args) {
    int a;
    while(1) {
        printf("Sou a filhinha da thread main...\n");
        var++;
    }
}

void* thread2(void* args) {
    int a;
    while(1) {
        printf("Sou a segunda filhinha da mamãe...\n");
        var++;
    }
}

int main(int argc, char const *argv[]) {

    int b;

    printf("Sou a thread main, muito prazer\n");
    printf("Sou uma thread. Que surpresa não?");

    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    while(1) {
            printf("Sou a thread mamain...\n");
            var++;
    }

    return 0;
}