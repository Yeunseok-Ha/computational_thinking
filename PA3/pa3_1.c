#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define INF 0x7fffffff

struct Edge{
	int source, destination;
};

struct Graph{
	int cities, rails;
	int* reachable_a, *reachable_b, *sum_fuel_a, *sum_fuel_b;
	struct Edge* railroad;
};

int dijkstra(struct Graph* graph, int source, int target, int fuel);
void graphCreation(struct Graph* g, int V, int E);
void graphConstruct(struct Graph* g, int index, int from, int to);

int main(void)
{
	int min_fuel, sum;
	int i, j, temp, p, q, r, N, M;
	int from, to;
//	struct Graph* alpha = (struct Graph*) malloc(sizeof(struct Graph));
//	struct Graph* beta = (struct Graph*) malloc(sizeof(struct Graph));
//	struct Graph* connect = (struct Graph*) malloc(sizeof(struct Graph));
	struct Graph* map = (struct Graph*) malloc(sizeof(struct Graph));

	scanf("%d %d %d %d %d",&p, &q, &r, &N, &M);
	
//	graphCreation(alpha, N, M);
//	graphCreation(beta, N, M);
//	graphCreation(connect, N, M);
	graphCreation(map, N, M);

	for(i = 0; i < M; i++){
		scanf("%d %d", &from, &to);
//		graphConstruct(alpha, i, from, to, p);
//		graphConstruct(beta, i, from, to, q);
//		graphConstruct(connect, i, from, to, r);
		graphConstruct(map, i, from, to);
	}

	min_fuel = dijkstra(map, 0, N-1, p) + dijkstra(map, 1, N-1, q);
	printf("%d\n", min_fuel);
	for(i = 0; i < N; i++){
		if((map->reachable_a[i]==1 && map->reachable_b[i])){
			sum = map->sum_fuel_a[i] + map->sum_fuel_b[i];
			temp = ((map->sum_fuel_a[N-1] - map->sum_fuel_a[i])/p) * r;
			sum += temp;
			if(sum < min_fuel)
				min_fuel = sum;
		} else if(map->reachable_a[i] && map->reachable_b[i] == 1){
			sum = map->sum_fuel_a[i] + map->sum_fuel_b[i];
			temp = ((map->sum_fuel_b[N-1] - map->sum_fuel_b[i])/q) * r;
			sum += temp;
//			printf("%d\n", sum);
			if(sum < min_fuel)
				min_fuel = sum;
		}
	}
	printf("%d", min_fuel);
	
//	for(i = 0; i < N; i++)
//		free(Adj_Mat[i]);
//	free(Adj_Mat);
	free(map->railroad);
	free(map->reachable_a);
	free(map->reachable_b);
	free(map->sum_fuel_a);
	free(map->sum_fuel_b);
	free(map);
	return 0;
}

void graphCreation(struct Graph* g, int V, int E)
{
	g->cities = V;
	g->rails = E;
	g->railroad = (struct Edge*) malloc(g->rails * sizeof(struct Edge));
	g->reachable_a = (int*)malloc(V * sizeof(int));
	g->reachable_b = (int*)malloc(V * sizeof(int));
	g->sum_fuel_a = (int*)malloc(V * sizeof(int));
	g->sum_fuel_b = (int*)malloc(V * sizeof(int));
}
void graphConstruct(struct Graph* g, int index, int from, int to)
{
	g->railroad[index].source = from;
	g->railroad[index].destination = to;
//	g->railroad[index].fuel = weight;
}

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
			int u = graph->railroad[j].source -1;
			int v = graph->railroad[j].destination -1;
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
