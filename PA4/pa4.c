#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b, int size);
int power(int a, int b);
int isEven(int a);
int main(void)
{
	int i, j, k, tmp, state, cnt, rod_num, num_disks, dst, count;
	int **rod = malloc(3*sizeof(int));
	scanf("%d %d", &num_disks, &dst);	
	
	for(i = 0; i<3; i++){
		rod[i] = (int*)malloc(num_disks*sizeof(int));
		scanf("%d ", &rod_num);
		for(j=0; j < rod_num; j++){
			scanf("%d", &tmp);
			rod[i][j] = tmp;
		}
	}
	
	if(dst != 3)
		swap(rod[2], rod[dst-1], num_disks);
	if(rod[1][0] == num_disks)
		swap(rod[0], rod[1], num_disks);
		

//	count = 1;
//	for(i = 0; i < num_disks; i++)
//		count *= 2;
//
//	count = (int)pow(2.0, (double)num_disks);
//	count -= 1;

	tmp = num_disks;
	i = 0;
	j = 0;
	k = 0;
	cnt = 0;
	count = 0;
	while(tmp && rod[0][i] == tmp){
		count += power(2, num_disks - tmp);
		i++;
		tmp--;
	}
	state = tmp;

	if(isEven(num_disks)){
		while(tmp){
			if(rod[0][i] == tmp && isEven(tmp)){
				
				i++;
			}else if(rod[0][i] == tmp && !isEven(tmp)){
				tmp--;
				i++;
			}else if(rod[1][j] == tmp && isEven(tmp)){
				count += power(2, num_disks - tmp) - (3*cnt+ + 2);
				tmp--;
				j++;
			}else if(rod[1][j] == tmp && !isEven(tmp)){
				count += power(2, num_disks - tmp) - (3*cnt + 1);
				tmp--;
				j++;
			}else if(rod[2][k] == tmp && isEven(tmp)){
				count += power(2, num_disks - tmp) - (3*cnt + 1);
				tmp--;
				k++;
			}else{
				count += power(2, num_disks - tmp) - (3*cnt + 2);
				tmp--;
				k++;
			}
			if(tmp % 3 == 0)
				cnt++;
		}
	}
       	
	else {
		while(state > 0){
			if(rod[i][j] == state && isEven(state)){

			}else if(rod[1][j] == state && !isEven(state)){

			}else if(rod[2][k] == state && isEven(state)){

			}else{

			}
		}

	}
	
	for(i = 0; i < 3; i++){
		for(j = 0; j < num_disks; j++)
			printf("%d ", rod[i][j]);
		printf("\n");
	}

	printf("%d", count);
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
