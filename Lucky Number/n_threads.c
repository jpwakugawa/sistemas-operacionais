#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
	srand(time(NULL));

	int n = atoi(argv[1]);
	int* X = (int*)(malloc(n * n * sizeof(int)));
	pthread_t th[n];

	// First barrier wait for n threads
	pthread_barrier_t barrier1;
	pthread_barrier_init(&barrier1, NULL, n);

	// Second barrier must have n+1 to wait for main()
	pthread_barrier_t barrier2;
	pthread_barrier_init(&barrier2, NULL, n+1);

	void* routine(void* arg) {
		int j = *(int*)arg;

		for(int i=0; i<n; i++) {
			if(i==0)
				X[i * n + j] = rand() % n;
			else 
				X[i * n + j] = X[((i-1) * n) + (rand()%n)];
			pthread_barrier_wait(&barrier1);
		}
		pthread_barrier_wait(&barrier2);
	}

	for(int j=0; j<n; j++) {
		int* a = malloc(sizeof(int));
		*a = j;

		if(pthread_create(&th[j], NULL, &routine, a) != 0)
			perror("Failed to create thread");
	}

	// Waiting for main() to finish
	pthread_barrier_wait(&barrier2);

	for(int j=0; j<n; j++) {
		if(pthread_join(th[j], NULL) != 0)
			perror("Failed to join thread");
	}

	if (n<=10) {

	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if (j==n-1)
				printf("%d\n", X[i * n + j]);
			else
				printf("%d ", X[i * n +j]);
		}
	}

	}

	pthread_barrier_destroy(&barrier1);
	pthread_barrier_destroy(&barrier2);
	free(X);

	return 0;
}
