#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define INF 0x7fffffff
#define SIZE 40000

struct queue {
	int items[SIZE];
	int front;
	int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);
struct node
{
	int vertex;
	struct node* next;
};
struct node* createNode(int);
struct Graph
{
	int numVertices;
	struct node** adjLists;
	int* visited;
	int *adj_count, *reachable_a, *reachable_b, *storePare_a, *storePare_b, *fromDst;
	int temp;
};
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void bfs(struct Graph* graph, int startVertex);
int main(void)
{
	int min_fuel, sum;
	int i, j, p, q, r, N, M;
	int from, to;

	scanf("%d %d %d %d %d",&p, &q, &r, &N, &M);
	
	struct Graph *map = createGraph(N);
	int *temp = malloc(sizeof(int) * N);

	for(i = 0; i < M; i++){
		scanf("%d %d", &from, &to);
		addEdge(map, from-1, to-1);
	}

	bfs(map, N-1);
	bfs(map, 0);
	bfs(map, 1);
	min_fuel = (map->reachable_a[N-1]*p) + (map->reachable_b[N-1]*q);
	
/*	for(i = 2; i < N; i++){
		if((map->storePare_a[i] == map->storePare_b[i])){
			j = i;
			while(map->storePare_a[j] == map->storePare_b[j]){
				j = map->storePare_a[j];
			}
			if(map->adj_count[j] > 2){
				sum = (map->reachable_a[j]*p) + (map->reachable_b[j]*q) + (map->fromDst[j]*r);
				if(sum < min_fuel)
					min_fuel = sum;
			}
			//printf("%dth temp : %d sum : %d\n ", i,temp, sum);
		}
	}
*/
	for(i = 0; i < N; i ++){
		if((map->storePare_a[i] == map->storePare_b[i]) && temp[i] != 1){
			j = i;
			while(map->storePare_a[j] == map->storePare_b[j]){
				j = map->storePare_a[j];
				//temp[j] = 1;
			}
			if(map->fromDst[j] != (map->reachable_a[N-1] - map->reachable_a[j]) 
					|| map->fromDst[j] != (map->reachable_b[N-1] - map->reachable_b[j])
					&& map->adj_count[j] > 2){
				sum = (map->reachable_a[j]*p) + (map->reachable_b[j]*q) +(map->fromDst[j]*r);
				if(sum < min_fuel)
					min_fuel = sum;
				//temp[j] = 1;
			}
		}
	}	
	printf("%d", min_fuel);
	free(temp);
	free(map);
	return 0;

}

void bfs(struct Graph* graph, int startVertex) {
	int *storeDist = malloc(sizeof(int)*(graph->numVertices));
	struct queue* q = createQueue();
	int a = 0;

	for(int i = 0; i < graph->numVertices; i++){
		graph->visited[i]=0;
		storeDist[i] = 0;
	}
	graph->visited[startVertex] = 1;
	enqueue(q, startVertex);
	
	graph->reachable_a[0] = 0;
	graph->reachable_b[1] = 0;

	while(!isEmpty(q)){
		int currentVertex = dequeue(q);
		
		struct node* temp = graph->adjLists[currentVertex];
						           
		while(temp) {
			int adjVertex = temp->vertex;
//			if((startVertex == 0) && (graph->fromDst[0] - graph->fromDst[currentVertex] == graph->reachable_a[currentVertex])){
//				break;
//			}else if((startVertex == 1) && (graph->fromDst[1] - graph->fromDst[currentVertex] == graph->reachable_b[currentVertex])){
//				break;
//			}

			if(graph->visited[adjVertex] == 0){
				storeDist[adjVertex] = storeDist[currentVertex]+1;
				if(startVertex == 0){
					graph->reachable_a[adjVertex] = storeDist[adjVertex];
					graph->storePare_a[adjVertex] = currentVertex;
				}
				else if(startVertex == 1){
					graph->reachable_b[adjVertex] = storeDist[adjVertex];
					graph->storePare_b[adjVertex] = currentVertex;
				}else{
					graph->fromDst[adjVertex] = storeDist[adjVertex];
//					graph->reachable_a[adjVertex] = storeDist[adjVertex];
//					graph->reachable_b[adjVertex] = storeDist[adjVertex];
				}
				graph->visited[adjVertex] = 1;
				enqueue(q, adjVertex);
			}
				temp = temp->next;
		}
	}
	printf("from %d : \n",startVertex);
	for(int i = 0; i < graph->numVertices; i++)
		printf("%d \t", storeDist[i]);
	printf("\n");
//	for(int i = 0; i < graph->numVertices; i++)
//		printf("%d \t", graph->reachable_b[i]);
//	printf("\n");
	free(q);
	free(storeDist);
}
 
struct node* createNode(int v)
{
	struct node* newNode = malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}
 
struct Graph* createGraph(int vertices)
{
	struct Graph* graph = malloc(sizeof(struct Graph));
	graph->numVertices = vertices;
		 
	graph->adjLists = malloc(vertices * sizeof(struct node*));
	graph->visited = malloc(vertices * sizeof(int));
	graph->reachable_a = malloc(vertices * sizeof(int));
	graph->reachable_b = malloc(vertices * sizeof(int));
	graph->storePare_a = malloc(vertices * sizeof(int));
	graph->storePare_b = malloc(vertices * sizeof(int));
	graph->adj_count = malloc(vertices * sizeof(int));
	graph->fromDst = malloc(vertices * sizeof(int));

	int i;
	for (i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
		graph->visited[i] = 0;
		graph->adj_count[i] = 0;
//		graph->reachable_a[i] = -1;
//		graph->reachable_b[i] = -1;
		graph->storePare_a[i] = -1;
		graph->storePare_b[i] = -1;
//		graph->fromDst[i] = -1;
	}
	
	return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest)
{
	struct node* newNode = createNode(dest);
	newNode->next = graph->adjLists[src];
	graph->adjLists[src] = newNode;
	graph->adj_count[src]++;
	              
	newNode = createNode(src);
	newNode->next = graph->adjLists[dest];
	graph->adjLists[dest] = newNode;
	graph->adj_count[dest]++;
}
struct queue* createQueue() {
        struct queue* q = malloc(sizeof(struct queue));
	q->front = -1;
	q->rear = -1;
	return q;
}
int isEmpty(struct queue* q) {
	if(q->rear == -1) 
		return 1;
	else 
	        return 0;
}
void enqueue(struct queue* q, int value){
	if(q->front == -1)
		q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
}
int dequeue(struct queue* q){
        int item;
	item = q->items[q->front];
	q->front++;
	if(q->front > q->rear){
	        q->front = q->rear = -1;
	}
        return item;
}
