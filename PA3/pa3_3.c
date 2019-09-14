#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define INF 0x7fffffff
#define SIZE 40000
//#define initial 0
//#define waiting 1
//#define visited 2

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
	int *reachable_a, *reachable_b, *storePare_a, *storePare_b;
	int temp;
};
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
int bfs(struct Graph* graph, int startVertex, int finishVertex);
int main(void)
{
	int min_fuel, sum;
	int i, j, temp, p, q, r, N, M;
	int from, to;
	//struct Graph* map = (struct Graph*) malloc(sizeof(struct Graph));

	scanf("%d %d %d %d %d",&p, &q, &r, &N, &M);
	
	struct Graph *map = createGraph(N);

	for(i = 0; i < M; i++){
		scanf("%d %d", &from, &to);
		addEdge(map, from-1, to-1);
	}
	min_fuel = (bfs(map, 0, N-1)*p) +(bfs(map, 1, N-1)*q);
	
	for(i = 0; i < N; i++){
		if((map->storePare_a[i] != map->storePare_b[i])){
			temp = bfs(map, i, N-1)*r;
			sum = (map->reachable_a[i]*p) + (map->reachable_b[i]*q) + temp;
			if(sum < min_fuel)
				min_fuel = sum;
			//printf("%dth temp : %d sum : %d\n ", i,temp, sum);
		}
	}
	
	printf("%d", min_fuel);
	free(map);
	return 0;

}

int bfs(struct Graph* graph, int startVertex, int finishVertex) {
	int *storeDist = malloc(sizeof(int)*(finishVertex+1));
	struct queue* q = createQueue();
	int returnDist;

	for(int i = 0; i < finishVertex+1; i++){
		graph->visited[i]=0;
		storeDist[i] = 0;
	}
	graph->visited[startVertex] = 1;
	enqueue(q, startVertex);

	while(!isEmpty(q)){
//		printQueue(q);
		int currentVertex = dequeue(q);
//		printf("Visited %d\n", currentVertex);
		
		struct node* temp = graph->adjLists[currentVertex];
						           
		while(temp) {
			int adjVertex = temp->vertex;
			if(graph->visited[adjVertex] == 0){
				storeDist[adjVertex] = storeDist[currentVertex]+1;
				if(startVertex == 0){
					graph->reachable_a[adjVertex] = storeDist[adjVertex];
					graph->storePare_a[adjVertex] = currentVertex;
				}
				else if(startVertex == 1){
					graph->reachable_b[adjVertex] = storeDist[adjVertex];
					graph->storePare_b[adjVertex] = currentVertex;
				}
				graph->visited[adjVertex] = 1;
				enqueue(q, adjVertex);
			}
//			if(adjVertex == finishVertex)
//				break;
//			else
				temp = temp->next;
		}
	}
//	printf("from %d : \n",startVertex);
//	for(int i = 0; i < finishVertex+1; i++)
//		printf("%d \t", graph->storePare_a[i]);
//	printf("\n");
//	for(int i = 0; i < finishVertex+1; i++)
//		printf("%d \t", graph->storePare_b[i]);
//	printf("\n");
	returnDist = storeDist[finishVertex];
	free(q);
	free(storeDist);
	return returnDist;
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
			 
	int i;
	for (i = 0; i < vertices; i++) {
		graph->adjLists[i] = NULL;
		graph->visited[i] = 0;
	}
	
	return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest)
{
	// Add edge from src to dest
	struct node* newNode = createNode(dest);
	newNode->next = graph->adjLists[src];
	graph->adjLists[src] = newNode;
	              
	// Add edge from dest to src
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
//        if(q->rear == SIZE-1)
//	        printf("\nQueue is Full!!");
//	else {
	        if(q->front == -1)
		        q->front = 0;
                q->rear++;
                q->items[q->rear] = value;
//	}
}
int dequeue(struct queue* q){
        int item;
//        if(isEmpty(q)){
//                printf("Queue is empty");
//        	item = -1;
//	}
//	else{
	        item = q->items[q->front];
	        q->front++;
		if(q->front > q->rear){
//		        printf("Resetting queue");
	                q->front = q->rear = -1;
		}
//	}
        return item;
}
void printQueue(struct queue *q) {
        int i = q->front;
        if(isEmpty(q)) {
	        printf("Queue is empty");
	} else {
	        printf("\nQueue contains \n");
	        for(i = q->front; i < q->rear + 1; i++) {
		        printf("%d ", q->items[i]);
	        }
	}    
}
