#include <stdio.h>
#include <stdlib.h>

struct info{
	long xi;
	long distance;
	int amplifier;
};

int valid = 0;
struct info* tmp;
void merge(struct info list[], int left, int mid, int right);
void merge_sort(struct info list[], int left, int right);
int main(void)
{
	int count, n, k, valid;
	long min_dist, total_distance, accum_dist;
	scanf("%d %d", &n, &k);

		
//	int *xi = (int*)malloc(n*sizeof(long long));
	struct info* point = malloc(n*sizeof(struct info));
//	int *dist= (int*)malloc((n-1)*sizeof(long long));
	for(int i = 0; i < n; i++){
		scanf("%ld", &point[i].xi);
	}
	tmp = malloc(n*sizeof(struct info));
	merge_sort(point, 0, n-1);	
	valid = 1;
	total_distance = point[n-1].xi - point[0].xi;
	count = 2;
	for(int i = 0; i < n-1; i++){
		point[i].distance = point[i+1].xi - point[i].xi;
	}

	merge_sort(point, 0, n-2);
	min_dist = total_distance/(k-count+1);
	for(int i = n-2; i > 0; i--){
		while(count <= k)
			if(point[i].distance > min_dist){
				point[i].amplifier = 1;
				total_distance -= point[i].distance;
				count++;
				min_dist = total_distance/(k-count+1);
			}else{
				
			}
	}
//	accum_dist = 0;
//	for(int i = 0; i < n-k+1; i++)
//		accum_dist += dist[i];
//	if(accum_dist < min_dist)
//		min_dist = accum_dist;
	
	free(tmp);
	free(point);
	printf("%ld", min_dist);
	return 0;
}

void merge(struct info list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left;
	j = mid+1;
	k = left;
	if(!valid){
		while(i <=mid && j <=right){
			if(list[i].xi <= list[j].xi)
				tmp[k++] = list[i++];
			else
				tmp[k++] = list[j++];
		}
		if(i>mid){
			for(l = j; l <=right; l++)
				tmp[k++] = list[l];
		}else{
			for(l=i; l <=mid; l++)
				tmp[k++] = list[l];
		}

		for(l = left; l <=right; l++)
			list[l] = tmp[l];
	}
	else{
		while(i <=mid && j <=right){
			if(list[i].distance <= list[j].distance)
				tmp[k++] = list[i++];
			else
				tmp[k++] = list[j++];
		}
		if(i>mid)
			for(l = j; l <=right; l++)
				tmp[k++] = list[l];
		else
			for(l = i; l <= mid; l++)
				tmp[k++] = list[l];
		for(l = left; l <=right; l++)
			list[l] = tmp[l];
	}
}

void merge_sort(struct info list[], int left, int right)
{
	int mid;
	if(left<right){
		mid = (left+right)/2;
		merge_sort(list, left, mid);
		merge_sort(list, mid+1, right);
		merge(list, left, mid, right);
	}
}
