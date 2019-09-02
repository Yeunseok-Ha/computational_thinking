#include <stdio.h>
#include <stdlib.h>


struct building{
	int g;
	int x;
};

void merge(struct building* list, int left, int mid, int right, struct building* sorted);
void merge_sort(struct building* list, int left, int right, struct building* sorted);
int main (void)
{
	int k, i, j, n, to;
	int sum_g = 0;
	int max_g = 0;
	int s = 0;
	
	struct building* b;
	//get numbers of buildings and waling distance
	scanf("%d %d", &n, &k);

	b = malloc(sizeof(struct building)*n);
	
	//get location of each buildings and its included people
	for(i = 0; i < n; i++){
		scanf("%d %d", &b[i].g, &b[i].x);
	}
	struct building* sorted = malloc(sizeof(struct building)*n);
	
	merge_sort(b, 0, n-1, sorted);
//	for(i = 0; i < n; i++)
//		printf("x : %d, g : %d\n", b[i].x, b[i].g);
	for(i = 0; i < n; i++){
		s = b[i].x;
		//from = i;
		to = i;
		while(s >= b[i].x && s <= b[i].x + (2*k) && s <= b[n-1].x ){
			sum_g += b[to].g;
			++to;
			s = b[to].x;
		}
		
		if(sum_g > max_g){
			max_g = sum_g;
		}
//		printf("sum_g : %d, max_g : %d\n",sum_g, max_g);
		sum_g = 0;
	}

	printf("%d", max_g);
	
	free(b);
	return 0;
}

void merge(struct building* list, int left, int mid, int right, struct building* sorted)
{
	int i, j, k, l;
	i = left;
	j = mid+1;
	k = left;

	while(i<=mid && j<=right){
		if(list[i].x <= list[j].x)	
			sorted[k++] = list[i++];
		else
		        sorted[k++] = list[j++];
	}
	
	if(i>mid){
		for(l=j; l<=right; l++)
			sorted[k++] = list[l];
	}
	else{
	        for(l=i; l<=mid; l++)
	                sorted[k++] = list[l];
	}
	
	for(l=left; l<=right; l++){
		list[l] = sorted[l];
	}
}

void merge_sort(struct building* list, int left, int right, struct building* sorted){
        int mid;
        if(left<right){
		mid = (left+right)/2;
		merge_sort(list, left, mid, sorted);
		merge_sort(list, mid+1, right, sorted);
		merge(list, left, mid, right, sorted);
	}
}
