#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>

void* f(void* args) {
    fork();
    while(1) {
        printf("Sou uma nova thread");
    }
}


int main() {
    int variavel = 10;
    int variavel2 = 20;

    pid_t pf = fork();

    pid_t pf2 = fork();

    if(pid_filho == 0 || pid_filho_2 == 0) {
        pthread_t thread;
        pthread_create(thread, NULL, f, NULL);
    }

    while(1) {
        printf("Sou a thread main");
    }

}