#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define INF 0x7fffffff

struct Edge{
	int source, destination, fuel;
};

struct Graph{
	int cities, rails;
	int* reachable, *sum_fuel;
	struct Edge* railroad;
};

int dijkstra(struct Graph* graph, int source, int target);
void graphCreation(struct Graph* g, int V, int E);
void graphConstruct(struct Graph* g, int index, int from, int to, int weight);

int main(void)
{
	int min_fuel, sum;
	int i, j, p, q, r, N, M;
	int from, to;
	struct Graph* alpha = (struct Graph*) malloc(sizeof(struct Graph));
	struct Graph* beta = (struct Graph*) malloc(sizeof(struct Graph));
	struct Graph* connect = (struct Graph*) malloc(sizeof(struct Graph));

	scanf("%d %d %d %d %d",&p, &q, &r, &N, &M);
	
	graphCreation(alpha, N, M);
	graphCreation(beta, N, M);
	graphCreation(connect, N, M);

	for(i = 0; i < M; i++){
		scanf("%d %d", &from, &to);
		graphConstruct(alpha, i, from, to, p);
		graphConstruct(beta, i, from, to, q);
		graphConstruct(connect, i, from, to, r);

	}

	min_fuel = dijkstra(alpha, 0, N-1) + dijkstra(beta, 1, N-1);

	for(i = 0; i < N; i++){
		if((alpha->reachable[i]==1 && beta->reachable[i]) ||
				(alpha->reachable[i] && beta->reachable[i] == 1)){
			sum = alpha->sum_fuel[i]
				+ beta->sum_fuel[i]
				+ dijkstra(connect,i,N-1);
			if(sum < min_fuel)
				min_fuel = sum;
		}
	}
	printf("%d", min_fuel);
	
//	for(i = 0; i < N; i++)
//		free(Adj_Mat[i]);
//	free(Adj_Mat);
	return 0;
}

void graphCreation(struct Graph* g, int V, int E)
{
	g->cities = V;
	g->rails = E;
	g->railroad = (struct Edge*) malloc(g->rails * sizeof(struct Edge));
	g->reachable = (int*)malloc(V * sizeof(int));
	g->sum_fuel = (int*)malloc(V * sizeof(int));
}
void graphConstruct(struct Graph* g, int index, int from, int to, int weight)
{
	g->railroad[index].source = from;
	g->railroad[index].destination = to;
	g->railroad[index].fuel = weight;
}

int dijkstra(struct Graph* graph, int source, int target)
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
			int fuel = graph->railroad[j].fuel;
			//printf("%d %d %d\n",u,v,fuel);
			if ((!visited[v]) && u == minIndex && minFuel + fuel < StoreFuel[v]){
				StoreFuel[v] = StoreFuel[u] + fuel;
				graph->sum_fuel[v] = StoreFuel[v];
				graph->reachable[v] = graph->reachable[u] +1;
			}
		}
		//printf(" ");
		count++;
	}
//	for(i = 0; i < V; i++)
//		printf("%d\t", graph->reachable[i]);
//	printf("\n");
//	printResult(StoreFuel, V);
	minFuel = StoreFuel[target];
	
	free(StoreFuel);
	free(StorePred);
	free(visited);

	return minFuel;
}
