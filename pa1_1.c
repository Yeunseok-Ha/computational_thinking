#include <stdio.h>
#include <stdlib.h>

#define MAX 10000000000

struct building{
	int g;
	long x;
};

void Swap(struct building* arr, int a, int b);
int Partition(struct building* arr, int left, int right);
void QuickSort(struct building* arr, int left, int right);

int main (void)
{
	int k, i, j, n, to;
	long sum_g = 0;
	long max_g = 0;
	long s = 0;

	struct building* b;
	//get numbers of buildings and waling distance
	scanf("%d %d", &n, &k);

	b = malloc(sizeof(struct building)*n);

	//get location of each buildings and its included people
	for(i = 0; i < n; i++){
		scanf("%d %ld", &b[i].g, &b[i].x);
	}

	QuickSort(b,0,n-1);
//	for(i = 0; i < n; i++)
//		printf("x:%ld g:%d\n",b[i].x, b[i].g);

	for(i = 0; i < n; i++){
		s = b[i].x;
		//from = i;
		to = i;
		while(s >= b[i].x && s <= b[i].x + (2*k) && s <= b[n-1].x ){
			if(s == b[to].x){
				sum_g += (long)b[to].g;
				to++;
			}
			s++;
		}
		if(sum_g > max_g)
			max_g = sum_g;
		sum_g = 0;
	}

	printf("%ld", max_g);
	
	free(b);
	return 0;
}

void Swap(struct building* arr, int a, int b)  
{
	struct building temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

int Partition(struct building* arr, int left, int right)
{
	struct building pivot = arr[left]; 
	int low = left + 1;
	int high = right;
		     
	while (low <= high) {
		while (pivot.x >= arr[low].x && low <= right) {
			low++;
		}
		while (pivot.x <= arr[high].x && high >= (left+1) ) {
			high--;
		}
		if (low <= high){
			Swap(arr, low, high);  
		}
	}
	Swap(arr, left, high);  
	return high;   		 
}
 
void QuickSort(struct building* arr, int left, int right)
{
	if (left <= right){
		int pivot = Partition(arr, left, right);
		QuickSort(arr, left, pivot - 1);
		QuickSort(arr, pivot + 1, right);
	}
}
 
