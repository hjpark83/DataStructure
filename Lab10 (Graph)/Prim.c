#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 7
#define INF 1000

int graph[MAX][MAX] = {
    {0, 28, INF, INF, INF, 10, INF},
    {28, 0, 16, INF, INF, INF, 14},
    {INF, 16, 0, 12, INF, INF, INF},
    {INF, INF, 12, 0, 22, INF, 18},
    {INF, INF, INF, 22, 0, 25, 24},
    {10, INF, INF, INF, 25, 0, INF},
    {INF, 14, INF, 18, 24, INF, 0},
};

int selected[MAX];  // vertex set
int dist[MAX];      // distance

int getMinVertex(int n){
    int v;
    for(int i = 0; i < n; i++){
        if(!selected[i]){
            v=i;
            break;
        }
    }
    for(int i = 0; i < n; i++){
        if(!selected[i] && dist[i]<dist[v])
            v=i;
    }
    return v;
}

void Prim(int s, int n){
    int u, v;
    for(u = 0; u < n; u++)
        dist[u] = INF;
    dist[s] = 0;

    for(int i = 0; i < n; i++){
        u = getMinVertex(n);
        selected[u] = TRUE;

        printf("%d -> ", u);
        for(v = 0; v < n; v++){
            if(graph[u][v] != INF)
                dist[v] = graph[u][v];
        }
    }
}

int main(){
    Prim(0, MAX);
    return 0;
}