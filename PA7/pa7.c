#include <stdio.h>
#include <stdlib.h>

struct info {
	int altitude;
	int valid;
};
int highest = 0;

int DFS(int** cell, struct info** trail, int i, int j, int n);
int main(void)
{
	int n;
	int temp = 0;
	int err = scanf("%d", &n);
	int** cell = (int**)malloc(n * sizeof(int**));
	struct info** trail = malloc(n * sizeof(struct info**));

	for (int i = 0; i < n; i++) {
		cell[i] = (int*)malloc(n * sizeof(int));
		trail[i] = malloc(n * sizeof(struct info));
		for (int j = 0; j < n; j++)
			err = scanf("%d", &cell[i][j]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			trail[i][j].altitude = 0;
			trail[i][j].valid = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			DFS(cell, trail, i, j, n);
		}
	}

	printf("%d", highest);
	return 0;
}

int DFS(int** cell, struct info** trail, int i, int j, int n)
{
	int temp = 0;
	trail[i][j].valid = 1;
	int modify = 0;
	int p = i;
	int q = j;
	int a = 0;

	if (q + 1 < n && cell[p][q] > cell[p][q + 1]) {					
		if (!trail[p][q + 1].valid) {
			trail[p][q + 1].altitude = DFS(cell, trail, p, q + 1, n);
		}
		temp = trail[p][q + 1].altitude + (cell[p][q] - cell[p][q + 1]);
		if (temp > trail[p][q].altitude)
			trail[p][q].altitude = trail[p][q + 1].altitude + (cell[p][q] - cell[p][q + 1]);			}
	if (q - 1 >= 0 && cell[p][q] > cell[p][q - 1]) {
		if (!trail[p][q - 1].valid) {
			trail[p][q - 1].altitude = DFS(cell, trail, p, q - 1, n);
		}
		temp = trail[p][q - 1].altitude + (cell[p][q] - cell[p][q - 1]);
		if (temp > trail[p][q].altitude)
			trail[p][q].altitude = trail[p][q - 1].altitude + (cell[p][q] - cell[p][q - 1]);
	}
	if (p + 1 < n && cell[p][q] > cell[p + 1][q]) {
		if (!trail[p + 1][q].valid) {
			trail[p + 1][q].altitude = DFS(cell, trail, p + 1, q, n);
		}
		temp = trail[p + 1][q].altitude + (cell[p][q] - cell[p + 1][q]);
		if (temp > trail[p][q].altitude)
			trail[p][q].altitude = trail[p + 1][q].altitude + (cell[p][q] - cell[p + 1][q]);
	}
	if (p - 1 >= 0 && cell[p][q] > cell[p - 1][q]) {
		if (!trail[p - 1][q].valid) {
			trail[p - 1][q].altitude = DFS(cell, trail, p - 1, q, n);
		}
		temp = trail[p - 1][q].altitude + (cell[p][q] - cell[p - 1][q]);
		if (temp > trail[p][q].altitude)
			trail[p][q].altitude = trail[p - 1][q].altitude + (cell[p][q] - cell[p - 1][q]);
	}
	if (trail[p][q].altitude > highest) {
		highest = trail[p][q].altitude;
	}
	return trail[p][q].altitude;
}

