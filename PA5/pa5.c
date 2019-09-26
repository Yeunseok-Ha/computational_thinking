#include <stdio.h>
#include <stdlib.h>
#include </usr/include/math.h>

int main(void)
{
	int n, tmp, count;

	scanf("%d", &n);
	int*** polyominos = (int***)malloc(n * sizeof(int**));
	int *h = malloc(n*sizeof(int));
	int *w = malloc(n*sizeof(int));

	count = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &h[i], &w[i]);
		polyominos[i] = (int**)malloc(h[i] * sizeof(int*));
		for (int j = 0; j < h[i]; j++) {
			polyominos[i][j] = (int*)malloc(w[i]*sizeof(int));
			for (int k = 0; k < w[i]; k++) {
				scanf("%d", &tmp);
				if (tmp == 1) {
					polyominos[i][j][k] = tmp*(i+1);
					count++;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < h[i]; j++) {
			for (int k = 0; k < w[i]; k++) {
				printf("%d ", polyominos[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}


//	if(sqrt(count)*sqrt(count) != (double)count){
//		printf("No solution possible");
//	} 
	
	
	if(count){
	
	}else{
		printf("No solution possible");
	}

	free(h);
	free(w);
	free(polyominos);
	return 0;
}

