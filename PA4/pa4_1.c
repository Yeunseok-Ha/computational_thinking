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
	int i, j, k, tmp, rod_num, num_disks, dst;
	long count;
	int **rod = malloc(3*sizeof(int));
	scanf("%d %d", &num_disks, &dst);	
	
	min_step = malloc(num_disks * sizeof(long));
	min_step[0] = 1;
	for(i = 1; i < num_disks; i++)
		min_step[i] = 2*min_step[i-1] +1;

	for(i = 0; i<3; i++){
		rod[i] = (int*)malloc(num_disks*sizeof(int));
		scanf("%d ", &rod_num);
		for(j=0; j < rod_num; j++){
			scanf("%d", &tmp);
			rod[i][j] = tmp;
		}
	}
	i = 0; j = 0; k = 0; tmp = num_disks;
	int *exist = malloc(num_disks * sizeof(int));
	
	if(dst != 3)
		swap(rod[2], rod[dst-1], num_disks);
	if(rod[1][0] == num_disks)
		swap(rod[0], rod[1], num_disks);

	while(tmp){
		if(rod[0][i] == tmp){
			exist[tmp-1] = 1;
			i++;
			tmp--;
		}else if(rod[1][j] == tmp){
			exist[tmp-1] = 2;
			j++;
			tmp--;
		}else{
			exist[tmp-1] = 3;
			tmp--;
		}
	}
	int *goal = malloc(num_disks*sizeof(int));
	for(i = 0; i < num_disks; i++){
//		if(isEven(i+1))
			goal[i] = 3;
//		else
//			goal[i] = 2;
	}

	count = 0;
	i = num_disks-1;
	while(i>=0){
//		if (isEven(i+1)){
			if(exist[i] != goal[i]){
				if(exist[i] == moveRight(goal[i])){
					goal[i] = moveRight(goal[i]);
					for(j = 0; j < i; j++)
						goal[j] = moveLeft(goal[j]);

				} else if(exist[i] == moveLeft(goal[i])){
					goal[i] = moveLeft(goal[i]);
					for(j = 0; j < i; j++)
						goal[j] = moveRight(goal[j]);
				}
				if(i ==0)
					count++;
				else
					count += min_step[i-1]+1;
//				printf("%ld\n",count);	
			}
				i--;
//		} else{

//		}
	}
	
	
	
	
//		for(j = 0; j < num_disks; j++)
//			printf("%d ", goal[j]);
//		printf("\n");

	printf("%ld", count);
	free(rod);
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
