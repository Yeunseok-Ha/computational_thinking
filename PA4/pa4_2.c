#include <stdio.h>
#include <stdlib.h>

int *min_step;

void swap(int *a, int *b, int size);
int power(int a, int b);
int isEven(int a);
int moveLeft(int a);
int moveRight(int a);
int main(void)
{
	int i, j, state, compare, tmp, rod_num, num_disks, dst;
	long count;
	int **rod = malloc(3*sizeof(int));
	scanf("%d %d", &num_disks, &dst);	
	
	min_step = malloc(num_disks * sizeof(long));
	min_step[0] = 1;
	for(i = 1; i < num_disks; i++)
		min_step[i] = 2*min_step[i-1] +1;
	int *exist = malloc(num_disks * sizeof(int));
	for(i = 0; i<3; i++){
		scanf("%d ", &rod_num);
		if(rod_num ==0)
			scanf("%d", &tmp);
		for(j=0; j < rod_num; j++){
			scanf("%d", &tmp);
			exist[tmp-1] = i+1;
		}
	}

	count = 0;	
	state = dst;
	i = num_disks-1;
	while(i>=0){
		if(exist[i] != state){
			if(exist[i] == moveRight(state)){
				state = moveLeft(state);
//				for(j = 0; j < i; j++)
//					goal[j] = moveLeft(goal[j]);
//				compare = moveLeft(compare);
			} else if(exist[i] == moveLeft(state)){
				state = moveRight(state);
//				for(j = 0; j < i; j++)
//					goal[j] = moveRight(goal[j]);
			}
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

	printf("%ld", count);
	free(rod);
//	free(goal);
	free(exist);
	free(min_step);
	return 0;
}

void swap(int *a, int *b, int size){
	for(int i = 0; i < size; i++){
		int temp = a[i];
		a[i] = b[i];
		b[i] = temp;
	}
}
int power(int a, int b){
	int result = 1;
	for(int i = 0; i < b; i ++)
		result *= a;
	return result;
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
