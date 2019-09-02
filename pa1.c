#include <stdio.h>
#include <stdlib.h>

#define MAX 10000000000
int main (void)
{
	int n, k, i, s, j;
	double sum_g_L = 0;
	double sum_g_R = 0;
	double max_g = 0;
	double min_x = MAX;
	double max_x = 0;

	//get numbers of buildings and waling distance
	scanf("%d %d", &n, &k);

	double *x = (double*)malloc(sizeof(double)*n);
	int *g = (int*)malloc(sizeof(int)*n);

	//get location of each buildings and its included people
	for(i = 1; i <= n; i++){
		scanf("%d %lf", &g[i-1], &x[i-1]);
		if(min_x > x[i-1])
			min_x = x[i-1];
		if(max_x < x[i-1])
			max_x = x[i-1];
	}

	for(i = 1; i <= n; i++){
		for(s = x[i-1]-(2*k); s <= x[i-1]; s++){
			for(j = 1; j <= n; j++){
				if(s >= min_x && s == x[j-1]){
					sum_g_L += g[j-1];
				}
			}
		}
		for(s = x[i-1]; s <= x[i-1]+(2*k); s++){
			for(j = 1; j <= n; j++){
				if(s < max_x && s == x[j-1]){
					sum_g_R += g[j-1];
				}
			}
		}
			if(sum_g_L > max_g)
				max_g = sum_g_L;
			if(sum_g_R > max_g)
				max_g = sum_g_R;
			//printf("from %lf, sum_g %lf\n",x[i-1], sum_g);
			//printf("max_g %lf\n",max_g);
			sum_g_L = 0;
			sum_g_R = 0;
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
