#include <cstdio>
#include <cstring>
using namespace std;

#define MAX 100

bool visited[MAX];

void DFS(int G[][MAX], int num, int v){
    
    visited[v] = true;
    printf("%d ", v);

    for(int i = 1; i <= num; ++i){
        if(G[v][i] != 0 && !visited[i]){
            DFS(G, num, i);
        }
    }
}

void DFSTraverse(int G[][MAX], int num){
    
    memset(visited, 0, sizeof(visited));
    int count = 0;

    for(int i = 1; i <= num; ++i){
        if(!visited[i]){
            printf("Level %d : ", ++count);
            DFS(G, num, i);
            printf("\n");
        }
    }
}

int main(){

    int n, m, u, v, w;
    int graph[MAX][MAX];
    
    FILE *fp = fopen("input", "r");
    while(fscanf(fp, "%d%d", &n, &m) != EOF){
        memset(graph, 0, sizeof(graph));
        for(int i = 0; i < m; ++i){
            fscanf(fp, "%d%d%d", &u, &v, &w);
            graph[u][v] = w;
            graph[v][u] = w;
        }   
        DFSTraverse(graph, n);
    }
}
