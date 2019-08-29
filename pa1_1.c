#include <stdio.h>
#include <stdlib.h>

#define MAX 10000000000
int main (void)
{
	int n, k, i, s, j;
	double min_x = MAX; 
	double max_x = 0;
	double sum_g = 0;
	double max_g = 0;

	//get numbers of buildings and waling distance
	scanf("%d %d", &n, &k);

	double *x = (double*)malloc(sizeof(double)*n);
	int *g = (int*)malloc(sizeof(int)*n);

	//get location of each buildings and its included people
	for(i = 1; i <= n; i++){
		scanf("%d %lf", &g[i-1], &x[i-1]);
		if(x[i-1] > max_x)
			max_x = x[i-1];
		if(x[i-1] < min_x)
			min_x = x[i-1];

	}

	for(i = min_x + k; i <= max_x - k; i++){
		for(s = x[i-1]-(k); s <= x[i-1]+(k); s++){
			for(j = 1; j <= n; j++){
				if(s >= 0 && s == x[j-1]){
					sum_g += g[j-1];
				}
			}
		}
			if(sum_g > max_g)
				max_g = sum_g;
			printf("from %lf, sum_g %lf\n",x[i-1], sum_g);
			printf("max_g %lf\n",max_g);
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