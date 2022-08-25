#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int start, end;
} Intervalo;

int *A, *B, *C;
int n;

void* soma(void* args) {
    Intervalo posicoes = *((Intervalo*)args);

    for(int i = posicoes.start ; i <= posicoes.end ; i++)
        C[i] = A[i] + B[i];
}

int main(int argc, char const *argv[]) {

    n = atoi(argv[1]);

    A = (int*)malloc(n * sizeof(int));
    B = (int*)malloc(n * sizeof(int));
    C = (int*)malloc(n * sizeof(int));

    pthread_t t1;
    Intervalo t1_intervalo;
    t1_intervalo.start = 0;
    t1_intervalo.end = (n/3)-1;

    pthread_create(&t1, NULL, soma, (void*)&t1_intervalo);

    pthread_t t2;
    Intervalo t2_intervalo;
    t2_intervalo.start = n/3;
    t2_intervalo.end = (2*(n/3))-1;

    pthread_create(&t2, NULL, soma, (void*)&t2_intervalo);

    pthread_t t3;
    Intervalo t3_intervalo;
    t3_intervalo.start = 2*(n/3);
    t3_intervalo.end = n-1;

    pthread_create(&t3, NULL, soma, (void*)&t3_intervalo);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    free(A);
    free(B);
    free(C);

    return 0;
}