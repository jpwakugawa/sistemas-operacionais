#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n = 10;

int main() {
	time_t begin = time(NULL);

	srand(time(NULL));
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

	time_t end = time(NULL);
	double exec_time = end - begin;
	printf("Execution Time: %f\n", exec_time);
	return 0;
}
