#include <stdio.h>
#include <stdlib.h>

#define MAX 100000
int sorted[MAX];

void merge(int list[], int left, int mid, int right);
void merge_sort(int list[], int left, int right);

int main (void)
{
	int i,j,n;
	int max_weight = 0;
	int count = 0;
	int max_carriers = 0;
	int bag[MAX];

	scanf("%d ", &max_weight);

	
	while( scanf("%d", &bag[i]) != EOF){
		i++;
	}
	n = i;
	
	merge_sort(bag, 0, n-1);
	i = 0;
	j = n-1;
	while(i != j){
		if(bag[i] + bag[j] <= max_weight){
			max_carriers++;
			i++;
			j--;
		} else {
			max_carriers++;
			j--;
		}
	}

	printf("%d", max_carriers);
//	printf("-------------------\n");
//	for(i = 0; i < n; n++){
//		printf("%d ", bag[i]);
//	}

	return 0;
}

void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left;
	j = mid+1;
	k = left;

	while(i<=mid && j<=right){
		if(list[i] <= list[j])	
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

void merge_sort(int list[], int left, int right){
        int mid;
        if(left<right){
		mid = (left+right)/2;
		merge_sort(list, left, mid);
		merge_sort(list, mid+1, right);
		merge(list, left, mid, right);
	}
}
