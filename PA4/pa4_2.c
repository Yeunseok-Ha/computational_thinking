#include <stdio.h>
#include <stdlib.h>

long long *min_step;

int isEven(int a);
int moveLeft(int a);
int moveRight(int a);
int main(void)
{
	int i, j, state, isFirst, tmp, rod_num, num_disks, dst;
	long long count;
	scanf("%d %d", &num_disks, &dst);	
	
	min_step = malloc(num_disks * sizeof(long long));
	min_step[0] = 1;
	for(i = 1; i < num_disks; i++)
		min_step[i] = 2*min_step[i-1] +1;
	int *exist = malloc(num_disks * sizeof(int));
	for(i = 0; i<3; i++){
		scanf("%d", &rod_num);
		for(j=0; j < rod_num; j++){
			scanf("%d", &tmp);
			exist[tmp-1] = i+1;
		}
	}
	isFirst = 1;
	count = 0;	
	state = dst;
	i = num_disks-1;
	while(i>=0){
		if(exist[i] != state){
			if(exist[i] == moveRight(state)){
				state = moveLeft(state);
			} else if(exist[i] == moveLeft(state)){
				state = moveRight(state);
			}
//			if(isFirst){
//				for(j = 1; j < i; j++)
//					min_step[j] = (min_step[j-1]<<1)+1;
//				isFirst = 0;
//			}
			if(i ==0)
				count++;
			else
				count += min_step[i-1]+1;
		}
		i--;
	}
	
	
	
	
//		for(j = 0; j < num_disks; j++)
//			printf("%d ", exist[j]);
//		printf("\n");

	printf("%lld", count);
//	free(rod);
	free(exist);
	free(min_step);
	return 0;
}
int isEven(int a){
	if(a % 2 == 0)
		return 1;
	else
		return 0;
}
int moveLeft(int a){
	if(a == 1)
		a = 3;
	else
		a--;
	return a;
}
int moveRight(int a){
	if (a == 3)
		a = 1;
	else
		a++;
	return a;
}
