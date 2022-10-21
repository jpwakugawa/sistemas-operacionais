#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	srand(time(NULL));

	int n = atoi(argv[1]);
	int* X = (int*)(malloc(n * n * sizeof(int)));

	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(i==0)
				X[i * n + j] = rand() % n;
			else 
				X[i * n + j] = X[((i-1) * n) + (rand()%n)];
		}
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

	free(X);

	return 0;
}
