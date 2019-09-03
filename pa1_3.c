#include <stdio.h>
#include <stdlib.h>


struct building{
	int g;
	int x;
};

//struct building b[10000000];
struct building sorted[10000000];
void merge(struct building list[], int left, int mid, int right);
void merge_sort(struct building list[], int left, int right);
int main (void)
{
	int k, i, j, n, from, to;
	int sum_g = 0;
	int max_g = 0;
	int s = 0;
	struct building b[1000000];	
//	struct building* b;
	scanf("%d %d", &n, &k);

//	b = malloc(sizeof(struct building)*n);
	
	for(i = 0; i < n; i++){
		scanf("%d %d", &b[i].g, &b[i].x);
	}
//	struct building* sorted = malloc(sizeof(struct building)*n);
	
	merge_sort(b, 0, n-1);
	for(i = 0; i < n; i++)
		printf("%d %d\n", b[i].x, b[i].g);

	from = 0;
	i = 0;
	while(i < n){
		s = b[i].x;
		//from = i;
		to = from;
		while(s <= b[i].x+(2*k) && to < n){
			if(b[from-1].x +(2*k) >= b[to].x)
				sum_g += b[to].g;
			to++;
			s = b[to].x;
//			printf("a\n");
		}
		if(sum_g > max_g){
			max_g = sum_g;
		}
		
		printf("to : %d sum_g : %d, b[i].g : %d\n",to, sum_g, b[i].g);
		
		sum_g -= b[i].g;
		from = to;
		
		if(b[i].x+(2*k) > b[n-1].x)
			break;
		else
			i++;
		
	}

	printf("%d", max_g);
	
//	free(b);
	return 0;
}

void merge(struct building list[], int left, int mid, int right)
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

void merge_sort(struct building list[], int left, int right){
        int mid;
        if(left<right){
		mid = (left+right)/2;
		merge_sort(list, left, mid);
		merge_sort(list, mid+1, right);
		merge(list, left, mid, right);
	}
}
