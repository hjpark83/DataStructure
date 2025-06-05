#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10

int visited[MAX_VERTICES];

typedef struct Queue{
    int queue[MAX_SIZE+1];
    int front;
    int rear;
}Queue;

typedef struct Graph{
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int n;
}Graph;

void init(Graph *g){
    g->n = 0;
    for(int i=0; i<MAX_VERTICES; i++){
        for(int j=0; j<MAX_VERTICES; j++){
            g->adjMatrix[i][j] = 0;
        }
    }
}

void initQueue(Queue* q){
    q->front = 0;
    q->rear = 0;
}

void insertVertex(Graph* g, int v){
    if(g->n == MAX_VERTICES){
        printf("Too many vertexes. Cannot insert node.\n");
        return;
    }
    g->n++;
}

void insertEdge(Graph* g, int u, int v){
    if(u >= g->n || v >= g->n){
        printf("Wrong vertex number. Vertex number should between 0~N-1\n");
        return;
    }
    g->adjMatrix[u][v] = 1;
    g->adjMatrix[v][u] = 1;
}

int isFull(Queue* q){
    return ((q->rear+1)%MAX_SIZE==q->front)?1:0;
}

int isEmpty(Queue* q){
    return (q->front==q->rear)?1:0;
}

void Enqueue(Queue* q, int data){
    if(isFull(q))
        printf("Queue is full\n");
    else{
        q->queue[q->rear] = data;
        q->rear = (q->rear+1)%MAX_SIZE;
    }
}

int Dequeue(Queue* q){
    int tmp = -1;
    if(isEmpty(q))
        printf("Queue is empty\n");
    else{
        tmp = q->queue[q->front];
        q->front = (q->front+1)%MAX_SIZE;
    }
    return tmp;
}

void BFS(Graph* g, int v){
    int w, search_v;
    Queue q;
    initQueue(&q);
    visited[v] = TRUE;
    Enqueue(&q, v);

    while(!isEmpty(&q)){
        search_v = Dequeue(&q);
        printf("%d -> ", search_v);

        for(w=0; w<MAX_VERTICES; w++){
            if(g->adjMatrix[search_v][w] == 1 && visited[w] == FALSE){
                visited[w] = TRUE;
                Enqueue(&q, w);
            }
        }
    }
}

int main(){
    Graph g;

    init(&g);
    for(int i=0; i<MAX_VERTICES; i++)
        visited[i] = FALSE;
    for(int i=0; i<7; i++)
        insertVertex(&g, i);

    insertEdge(&g, 0, 4);
    insertEdge(&g, 0, 6);
    insertEdge(&g, 1, 3);
    insertEdge(&g, 3, 5);
    insertEdge(&g, 4, 1);
    insertEdge(&g, 4, 2);
    insertEdge(&g, 6, 2);

    BFS(&g, 0);
}