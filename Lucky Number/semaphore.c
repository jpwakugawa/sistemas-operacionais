#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>


int main(int argc, char *argv[]) {
  srand(time(NULL));

	int n = atoi(argv[1]);
	int* X = (int*)(malloc(n * n * sizeof(int)));
	pthread_t th[n*n];
  sem_t semaphore[n*n];

  for(int i=0; i<n*n; i++) {
    sem_init(&semaphore[i], 0, n);
  }

	void* routine(void* arg) {
		int i = *(int*)arg;

    if(i < n) {
      X[i] = rand() % n;
    }
  }

	for(int i=0; i<n*n; i++) {
		int* a = malloc(sizeof(int));
		*a = i;

		if(pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to create thread");
	}

  for(int i=0; i<n; i++) {
    if(pthread_join(th[i], NULL) != 0) {
      perror("Failed to join thread");
    }
  }

  return 0;
}