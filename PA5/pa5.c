#include <stdio.h>
#include <stdlib.h>
#include </usr/include/math.h>

int main(void)
{
	int n, h, w, tmp, count;

	scanf("%d", &n);
	int*** polyominos = (int***)malloc(n*sizeof(int**));

	count = 0;
	for(int i = 0; i < n; i++){
		scanf("%d %d", &h, &w);
		polyominos[i] = (int**)malloc(h*sizeof(int*));
		for(int j = 0; j < h; j++){
			polyominos[i][h] = (int*)malloc(w*sizeof(int));
			for(int k = 0; k < w; k++){
				scanf("%d", &tmp);
				if(tmp==1){
					polyominos[i][h][w] = tmp+i;
					count++;
				}
			}
		}


	}



//	if(sqrt(count)*sqrt(count) != (double)count){
//		printf("No solution possible");
//	} 
	
	
	if(count){
	
	}else{
		printf("No solution possible");
	}

	free(polyominos);
	return 0;
}

