#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	int n, k, i, s, j;
	double sum_g = 0;
	double max_g = 0;

	//get numbers of buildings and waling distance
	scanf("%d %d", &n, &k);

	double *x = (double*)malloc(sizeof(double)*n);
	int *g = (int*)malloc(sizeof(int)*n);

	//get location of each buildings and its included people
	for(i = 1; i <= n; i++){
		scanf("%d %lf", &g[i-1], &x[i-1]);
	}

	for(i = 1; i <= n; i++){
		for(s = x[i-1]-(2*k); s <= x[i-1]+(2*k); s++){
			for(j = 1; j <= n; j++){
				if(s >= 0 && s == x[j-1]){
					sum_g += g[j-1];
				}
			}
		}
		if(sum_g > max_g)
			max_g = sum_g;
		sum_g = 0;
	}
	printf("%.0lf", max_g);
	/*
	printf("%d %d\n",n, k);
	for(i = 0; i < n; i++){
		printf("%d %lf\n", g[i], x[i]);
	}
	*/
	return 0;
}
