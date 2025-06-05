#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct Graph{
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int n; // vertex 개수
} Graph;

void init(Graph* g){
    g->n = 0;
    for(int i=0; i<MAX_VERTICES; i++){
        for(int j=0; j<MAX_VERTICES; j++){
            g->adjMatrix[i][j] = 0;
        }
    }
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

void DFS(Graph* g, int v){
    int w;
    visited[v] = TRUE;
    printf("%d -> ", v);

    for(w=0; w<MAX_VERTICES; w++){
        if(g->adjMatrix[v][w] == 1 && visited[w] == FALSE)
            DFS(g, w);
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

    DFS(&g, 0);
}