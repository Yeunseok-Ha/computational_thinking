#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define INF 0x7fffffff
#define SIZE 40000

int min_fuel = INF;
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
	int *adj_count, *reachable_a, *reachable_b, *fromDst;
	int temp;
};
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void bfs(struct Graph* graph, int startVertex, int fuel);
int main(void)
{
	int i, j, p, q, r, N, M;
	int from, to;

	scanf("%d %d %d %d %d",&p, &q, &r, &N, &M);
	
	struct Graph *map = createGraph(N);

	for(i = 0; i < M; i++){
		scanf("%d %d", &from, &to);
		addEdge(map, from-1, to-1);
	}

	bfs(map, 0, p);
	bfs(map, 1, q);
	min_fuel = (map->reachable_a[N-1]) + (map->reachable_b[N-1]);
	bfs(map, N-1, r);
	
	printf("%d", min_fuel);
	free(map);
	return 0;

}

void bfs(struct Graph* graph, int startVertex, int fuel) {
	int *storeDist = malloc(sizeof(int)*(graph->numVertices));
	struct queue* q = createQueue();
	int sum;

	for(int i = 0; i < graph->numVertices; i++){
		graph->visited[i]=0;
		storeDist[i] = 0;
	}
	graph->visited[startVertex] = 1;
	enqueue(q, startVertex);
	
	while(!isEmpty(q)){
		int currentVertex = dequeue(q);
		
		struct node* temp = graph->adjLists[currentVertex];
		int adjVertex = temp->vertex;
		
		while(temp) {
			adjVertex = temp->vertex;

			if(graph->visited[adjVertex] == 0){
				storeDist[adjVertex] = storeDist[currentVertex]+1;
				if(startVertex == 0){
					graph->reachable_a[adjVertex] = storeDist[adjVertex] * fuel;
				}
				else if(startVertex == 1){
					graph->reachable_b[adjVertex] = storeDist[adjVertex] * fuel;
				}else{
					graph->fromDst[adjVertex] = storeDist[adjVertex] * fuel;
					sum = graph->fromDst[adjVertex] + graph->reachable_a[adjVertex] + graph->reachable_b[adjVertex];
					if(sum < min_fuel)
						min_fuel = sum;
				}
				graph->visited[adjVertex] = 1;
				enqueue(q, adjVertex);
			}
				temp = temp->next;
		}
	}
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
	graph->fromDst = malloc(vertices * sizeof(int));

	int i;
	for (i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
		graph->visited[i] = 0;
	}
	
	return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest)
{
	struct node* newNode = createNode(dest);
	newNode->next = graph->adjLists[src];
	graph->adjLists[src] = newNode;
	              
	newNode = createNode(src);
	newNode->next = graph->adjLists[dest];
	graph->adjLists[dest] = newNode;
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
