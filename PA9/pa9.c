#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int** subjoint;
int min_total_time = 0;
int pairing(int* pipe, int from, int to);
int main(void)
{
	int n;

//	FILE* f = fopen("PA9_6.txt", "r");
	int err = scanf("%d", &n);
//	fscanf(f, "%d\n", &n);

	int* pipe = malloc(n * sizeof(int));
	subjoint = (int**)malloc(n * sizeof(int**));
	for (int i = 0; i < n; i++) {
		err = scanf("%d ", &pipe[i]);
//		fscanf(f, "%d ", &pipe[i]);
		subjoint[i] = (int*)malloc(n * sizeof(int));
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			subjoint[i][j] = INT_MAX;

	min_total_time = pairing(pipe, 0, n - 1);
	printf("%d", min_total_time);
	free(pipe);
	free(subjoint);
	return 0;
}

int pairing(int* pipe, int from, int to)
{
	for (int i = from; i <= to; i++) {
		subjoint[i][i] = 0;
		if (i != to) {
			subjoint[i][i + 1] = pipe[i + 1] + pipe[i];
			subjoint[i+1][i] = pipe[i + 1] + pipe[i];
		}
	}

	for (int r = 2; r <= to+1; r++)
		for (int i = from; i <= to - r + 1; i++) {
			int j = i + r - 1;
			subjoint[i][j] = INT_MAX;
			int length = 0;
			for (int t = i; t <= j; t++)
				length += pipe[t];
			for (int k = i; k <= j - 1; k++) {
				int q;
				q = subjoint[i][k] + subjoint[k + 1][j] + length;
				if (q < subjoint[i][j]) 
					subjoint[i][j] = q;
			}
	}
	return subjoint[from][to];
}
