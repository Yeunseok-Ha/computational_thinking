#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define INF 0x7fffffff
#define initial 0
#define waiting 1
#define visited 2

struct AdjMat{
	int adj_mat**;
};
struct Edge{
	int source, destination;
};

struct Graph{
	int cities, rails;
	int* reachable_a, *reachable_b;
	struct Edge* railroad;
};

void graphCreation(struct AdjMat** adj_mat, int V);
void graphConstruct(struct AdjMat** adj_mat, int index, int from, int to);
int BFS(struct Graph* g, int source, int target);

int main(void)
{
	int min_fuel, sum;
	int i, j, temp, p, q, r, N, M;
	int from, to;
//	struct Graph* map = (struct Graph*) malloc(sizeof(struct Graph));
	struct AdjMat** map;
	scanf("%d %d %d %d %d",&p, &q, &r, &N, &M);
	
	graphCreation(map, N;

	for(i = 0; i < M; i++){
		scanf("%d %d", &from, &to);
		graphConstruct(map, i, from, to);
	}
	min_fuel = (BFS(map, 0, N-1)*p) +(BFS(map, 1, N-1)*q);

	for(i = 0; i < N; i++){
		if((map->reachable_a[i] && map->reachable_b[i])){
			sum = (map->reachable_a[i]*p) + (map->reachable_b[i]*q) + (BFS(map,i,N-1)*r);
			if(sum < min_fuel)
				min_fuel = sum;
		}
	}
	
	printf("%d", min_fuel);
	
	free(map->railroad);
	free(map->reachable_a);
	free(map->reachable_b);
	free(map);
	return 0;
}

void graphCreation(struct AdjMat** adj_mat, int V)
{
	adj_mat = malloc(V*sizeof(int*));
	for(int i = 0; i < V; i++)
		adj_mat[i] = malloc(V*sizeof(int));

//	g->cities = V;
//	g->rails = E;
//	g->railroad = (struct Edge*) malloc(g->rails * sizeof(struct Edge));
//	g->reachable_a = (int*)malloc(V * sizeof(int));
//	g->reachable_b = (int*)malloc(V * sizeof(int));
}
void graphConstruct(struct AdjMat** adj_mat, int index, int from, int to)
{
	adj_mat[from-1][to-1] = 1;
	adj_mat[to-1][from-1] = 1;
	g->railroad[index].source = from-1;
	g->railroad[index].destination = to-1;
//	g->railroad[index].fuel = weight;
}
int BFS(struct Graph* g, int source, int target)
{
	int V = g->cities;
	int E = g->rails;
	int *StoreDist = malloc(sizeof(int)*V);
	int *StorePred = malloc(sizeof(int)*V);
	int *v_visited = malloc(sizeof(int)*V);
	int *queue = malloc(sizeof(int)*V);
	int i, u, v, front, rear, min_dist;

	for(i = 0; i<V; i++){
		StoreDist[i] = INF;
		StorePred[i] = -1;
		v_visited[i] = initial;
		queue[i] = -1;
	}
	StoreDist[source] = 0;
	v_visited[source] = waiting;
	front = 0;
	rear = 0;
	queue[rear] = source;
	rear++;

	while(front != rear){
		u = queue[front];
		front++;

		for(i = 0; i < E; i++){
			v = g->railroad[i].destination;
			if (u == g->railroad[i].source && v_visited[v] == initial){
				v_visited[v] = waiting;
				StoreDist[v] = StoreDist[u] +1;
				if(source == 0)
					g->reachable_a[v] = StoreDist[v];
				else if(source == 1)
					g->reachable_b[v] = StoreDist[v];
				StorePred[v] = u;
				queue[rear] = v;
				rear++;
			}
		}
		v_visited[u] = visited;
		if(v_visited[target] > 0)
			break;
	}
//	for(i = 0; i<V; i++)
//		printf("%d\t",g->reachable_a[i]);
//	printf("\n");
//	for(i = 0; i<V; i++)
//		printf("%d\t",g->reachable_b[i]);
//	printf("\n");

	min_dist = StoreDist[target];
	free(StoreDist);
	free(StorePred);
	free(v_visited);
	free(queue);

	return min_dist;
}

/*
int dijkstra(struct Graph* graph, int source, int target, int fuel)
{
	int V = graph->cities;
	int E = graph->rails;
	int *StoreFuel = malloc(sizeof(int)*V);
	int *StorePred = malloc(sizeof(int)*V);
	int *visited = malloc(sizeof(int)*V);
	int i, j, count, minFuel, minIndex;

	//initialize 
	for (i = 0; i<V; i++){
		StoreFuel[i] = INF;
		visited[i] = 0;
	}
	
	StoreFuel[source] = 0;
	count = 1;
	
	while (count <= V-1){
		minFuel = INF;
	
		//minIndex gives the node at minimum distance
		for (i = 0; i < V; i++) {
			if ((!visited[i]) && StoreFuel[i] < minFuel) {
				minFuel = StoreFuel[i];
				minIndex = i;
			}
		}
		//turn minIndex's node to visited
		visited[minIndex] = 1;

		for (j = 0; j < E; j++) {
			int u = graph->railroad[j].source;
			int v = graph->railroad[j].destination;
			//int fuel = graph->railroad[j].fuel;
			//printf("%d %d %d\n",u,v,fuel);
			if ((!visited[v]) && u == minIndex && minFuel + fuel < StoreFuel[v]){
				StoreFuel[v] = StoreFuel[u] + fuel;
				if(source == 0){
					graph->sum_fuel_a[v] = StoreFuel[v];
					graph->reachable_a[v] = graph->reachable_a[u] +1;
				} else if(source ==1){
					graph->sum_fuel_b[v] = StoreFuel[v];
					graph->reachable_b[v] = graph->reachable_b[u] +1;
				}
			}
		}
		//printf(" ");
		count++;
	}
//	for(i = 0; i < V; i++)
//		printf("%d\t", graph->sum_fuel_a[i]);
//	printf("\n");
//	for(i = 0; i < V; i++)
//		printf("%d\t", graph->sum_fuel_b[i]);
//	printf("\n");

//	printResult(StoreFuel, V);
	minFuel = StoreFuel[target];
	
	free(StoreFuel);
	free(StorePred);
	free(visited);

	return minFuel;
}
*/
