#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int buffer[10];
int count = 0;

void* producer(void* args) {
  // Produce
  int x = rand() % 100;

  // Add to the buffer
  buffer[count] = x;
  count ++;
}

void* consumer(void* args) {
  // Remove from the buffer
  int y = buffer[count-1];
  count--;

  // Consume
  printf("Got %d\n", y);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

	int n = atoi(argv[1]);
	pthread_t th[n];

  for(int i=0; i<n; i++) {
    if(i%2==0) {
      if(pthread_create(&th[i], NULL, &producer, NULL) != 0) {
        perror("Failed to create thread");
      }
    } else {
      if(pthread_create(&th[i], NULL, &consumer, NULL) != 0) {
        perror("Failed to create thread");
      }
    }
  }

  for(int i=0; i<n; i++) {
    if(pthread_join(th[i], NULL) != 0) {
      perror("Failed to join thread");
    }
  }

  return 0;
}