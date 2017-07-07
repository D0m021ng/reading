#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define MAX 100

bool visited[MAX];

void BFSTraverse(int (*G)[MAX], int num){
    memset(visited, 0, sizeof(visited));
    queue<int> Q;
    int count = 0;

    for(int i = 1; i <= num; ++i){
        if(!visited[i]){
            visited[i] = true;
            printf("Graph Level %d: %d ", ++count, i);
            Q.push(i);

            while(!Q.empty()){
                int p = Q.front();
                Q.pop();
                for(int j = 1; j <= num; ++j){
                    if(G[p][j] != 0 && !visited[j]){
                        visited[j] = true;
                        printf("%d ", j);
                        Q.push(j);
                    }
                }
            }
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
        BFSTraverse(graph, n);
    }
}
