#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
	srand(time(NULL));
	clock_t begin = clock();

	int n = atoi(argv[1]);
	int X[n][n];

	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(i==0)
				X[i][j] = rand() % n;
			else 
				X[i][j] = X[i-1][rand()%n];
		}
	}

	if (n<=10) {

	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if (j==n-1)
				printf("%d\n", X[i][j]);
			else
				printf("%d ", X[i][j]);
		}
	}

	}

	clock_t end = clock();
	double exec_time = end - begin;
	printf("Execution Time: %f\n", exec_time);
	return 0;
}
