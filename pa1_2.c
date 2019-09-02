#include <stdio.h>
#include <stdlib.h>

#define MAX 10000000000
int main (void)
{
	int n, k, i, j;
	long sum_g_L = 0;
//	int sum_g_R = 0;
	long max_g = 0;
	long s = 0;
	long min_x = MAX;
//	int max_x = 0;
	int count = 0;
	
	//get numbers of buildings and waling distance
	scanf("%d %d", &n, &k);
	
	int *x = (int*)malloc(sizeof(long)*n);
	int *g = (int*)malloc(sizeof(int)*n);
	
	//get location of each buildings and its included people
	for(i = 1; i <= n; i++){
		scanf("%d %d", &g[i-1], &x[i-1]);
		if(min_x > x[i-1])
			min_x = x[i-1];
//		if(max_x < x[i-1])
//			max_x = x[i-1];
	}

	for(i = 1; i <= n; i++){
		for(s = x[i-1]-(2*k); s <= x[i-1]; s++){
			if(s < min_x) break;
			for(j = 1; j <= n; j++){
				if(s == x[j-1]){
					sum_g_L += (long)g[j-1];
				//	printf("s:%ld x[j-1]:%d x[i-1]:%d sum_g_L:%ld\n",s,x[j-1],x[i-1], sum_g_L);
				}
			//	printf("%ld : %d : %d : %ld \n", s, x[j-1], x[i-1], sum_g_L);
			}
			//printf("%ld : %ld : %ld \n", s, x[i-1], sum_g_L);
		}

		if(sum_g_L > max_g)
			max_g = sum_g_L;
		sum_g_L = 0;
	}

	printf("%ld", max_g);
	return 0;
}	
