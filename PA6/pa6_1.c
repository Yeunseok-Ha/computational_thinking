#include <stdio.h>
#include <stdlib.h>

int* xi_sorted;
void merge(int* xi, int left, int mid, int right);
void merge_sort(int* xi, int left, int right);
int main(void)
{
	int count, n, k, valid;
	long long min_dist, distance, accum_dist;
	scanf("%d %d", &n, &k);
	
	int *xi = (int*)malloc(n*sizeof(long long));
	xi_sorted = (int*)malloc(n*sizeof(long long));
	int *dist = (int*)malloc((n-1)*sizeof(long long));
	for(int i = 0; i < n; i++)
		scanf("%d", &xi[i]);
	
	merge_sort(xi, 0, n-1);	
	for(int i = 0; i < n-1; i++)
		dist[i] = xi[i+1] - xi[i];

	merge_sort(dist, 0, n-2);
	min_dist = dist[n-k+1];
	accum_dist = 0;
	for(int i = 0; i < n-k+1; i++)
		accum_dist += dist[i];
	if(accum_dist < min_dist)
		min_dist = accum_dist;
	
	free(xi);
	free(xi_sorted);
	free(dist);
	printf("%lld", min_dist);
	return 0;
}

void merge(int *xi, int left, int mid, int right)
{
	int i, j, k, l;
	i = left;
	j = mid+1;
	k = left;

	while(i <=mid && j <=right){
		if(xi[i] <= xi[j])
			xi_sorted[k++] = xi[i++];
		else
			xi_sorted[k++] = xi[j++];
	}
	if(i>mid){
		for(l = j; l <=right; l++)
			xi_sorted[k++] = xi[l];
	}else{
		for(l=i; l <=mid; l++)
			xi_sorted[k++] = xi[l];
	}

	for(l = left; l <=right; l++)
		xi[l] = xi_sorted[l];
}

void merge_sort(int* xi, int left, int right)
{
	int mid;
	if(left<right){
		mid = (left+right)/2;
		merge_sort(xi, left, mid);
		merge_sort(xi, mid+1, right);
		merge(xi, left, mid, right);
	}
}
