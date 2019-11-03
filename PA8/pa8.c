#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct {
	int x;
	int rad;
	float expand;
} Balloon;

void calculateExpansion(Balloon* point, int from, int to);
int checkOverlapping(Balloon* point, int a, int b);
int main(void)
{
	int n;
	FILE* f = fopen("PA8_6.txt", "r");
//	int err = scanf("%d", &n);
	fscanf(f, "%d\n", &n);
	Balloon* point = malloc(n * sizeof(Balloon));

	for (int i = 0; i < n; i++) {
		err = scanf("%d %d", &point[i].x, &point[i].rad);
		fscanf(f, "%d %d\n", &point[i].x, &point[i].rad);
	}

	point[0].expand = point[0].rad;
	int j = 0;
	for (int i = 1; i < n; i++) {
		int left = j;
		int right = i-1;
		int mid = (left + right) / 2;
		calculateExpansion(point, mid, i);

		while (left < right) {
			if (checkOverlapping(point, right, i)) {
				left = mid + 1;
			}
			else if(checkOverlapping(point,left, i)){
				right = mid;
			}
			else {
				break;
			}
			mid = (left + right) / 2;	
			calculateExpansion(point, mid, i);
		}
	}
	for(int i = 0; i < n; i++) {
		printf("%0.3f\n", point[i].expand);
	}
	free(point);
			
	return 0;
}

void calculateExpansion(Balloon *point, int from, int to){
	float temp;
	if (pow(point[to].x - point[from].x, 2) + pow(point[to].rad - point[from].expand, 2) > pow(point[to].rad + point[from].expand, 2)) {
		temp = point[to].rad;
	}
	else {
		temp = pow(point[to].x - point[from].x, 2) / (4 * point[from].expand);
	}

	if(point[to].expand <=0)
		point[to].expand = temp;
	if (point[to].expand > temp)
		point[to].expand = temp;
}

int checkOverlapping(Balloon* point, int a, int b) {
	if (pow(point[a].x - point[b].x, 2) + pow(point[a].expand - point[b].expand, 2) < pow(point[a].expand + point[b].expand, 2))
		return 1;
	else
		return 0;
}
