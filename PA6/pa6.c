#include <stdio.h>
#include <stdlib.h>

int* temp;
void merge(int* xi, int left, int mid, int right);
void merge_sort(int* xi, int left, int right);
int main(void)
{
	int count, i, n, k, valid;
	long long min_dist, distance, accum_dist;
	scanf("%d %d", &n, &k);
	
	int *xi = (int*)malloc(n*sizeof(long long));
	temp = (int*)malloc(n*sizeof(long long));
	int *dist = (int*)malloc((n-1)*sizeof(long long));
	for(i = 0; i < n; i++)
		scanf("%d", &xi[i]);
	
	merge_sort(xi, 0, n-1);	
	for(i = 0; i < n-1; i++)
		dist[i] = xi[i+1] - xi[i];
	int range = xi[n-1] - xi[0];
	min_dist = range/(k-1);
	valid = 0;
	count = 2;

	for(i =0; i < n; i++)
		temp[i] = 0;
	temp[0] = 1;
	temp[n-1] = 1;

	distance = min_dist;
	accum_dist = 0;
	i = 0;
	while(count < k){
		if(//temp[i+1] == 0 && 
				accum_dist + dist[i] <= distance){
			accum_dist += dist[i];
			valid = 1;
		}else{
			if(!valid)
				accum_dist = dist[i];
			if(accum_dist < min_dist)
				min_dist = accum_dist;
			range -= accum_dist;
			distance = range/(k-count+1);
			accum_dist = 0;
			count++;
		}
		i++;
		if(i == n-1){
			i = 0;
			//distance = min_dist/(k-count+1);
		}
	}

	printf("%lld", min_dist);
	
	free(xi);
	free(temp);
	free(dist);
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
			temp[k++] = xi[i++];
		else
			temp[k++] = xi[j++];
	}
	if(i>mid){
		for(l = j; l <=right; l++)
			temp[k++] = xi[l];
	}else{
		for(l=i; l <=mid; l++)
			temp[k++] = xi[l];
	}

	for(l = left; l <=right; l++)
		xi[l] = temp[l];
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
