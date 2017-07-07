#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
using namespace std;

#define MAXN 101
#define INF  (1<<20)

void ShortestPath_Dijkstra(int G[][MAXN], int vexnum, int v0, int *P, int *D){
     int v, w;
     bool used[MAXN];
        
     memset(used, 0, sizeof(used));
     for(v = 0; v < vexnum; ++v){
         D[v] = G[v0][v];
         if(D[v] < INF)
            P[v] = v0;
         else
            P[v] = -1;
     }

     used[v0] = true;
     // P[v0] = v0;
     D[v0] = 0;

     for(int i = 1; i < vexnum; ++i){
        int min = INF;
        for(w = 0; w < vexnum; ++w)
            if(!used[w] && D[w] < min){
                v = w;
                min = D[w];
            }
        used[v]= true;        
        
        for(w = 0; w < vexnum; ++w)
            if(!used[w] && (min + G[v][w] < D[w])) {
                D[w] = min + G[v][w];
                P[w] = v;
            }
     }
}

void show_path(int *path, int v0, int v){
      stack<int> s;

      while(v != v0){
        s.push(v);
        v = path[v];
      }
      s.push(v);

      cout << "The path : ";   
      while(!s.empty()){
        cout << s.top() << " ";
        s.pop();
      }
      cout << endl;
}

int main(int argc, char *argv[]){
    
    int N, M, K, graph[MAXN][MAXN], D[MAXN], path[MAXN];
    bool pt[MAXN][MAXN];
    
    ifstream fin("input_shortestpath");
    while(fin>> N >> M >> K){
        int i, u, v, w;
        for(u = 0; u < N; ++u)
            for(v = 0; v < N; ++v){
                graph[u][v] = INF;
            }

        for(i = 0; i < M; ++i){
            fin >> u >> v >> w;
            graph[u][v] = w;
        }
        ShortestPath_Dijkstra(graph, N, K, path, D);
        for(i = 0; i < N; ++i){
            cout << "The shortest path 1 -> " << i; 
            if(D[i] < INF && D[i] > 0){
                cout << " is " << D[i] << endl;
                show_path(path, K, i);
            }else{
                cout << " NO!" << endl;
            }
        }
    }

    return 0;
}
