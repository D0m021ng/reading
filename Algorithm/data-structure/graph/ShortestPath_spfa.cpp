#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;

#define MAXN 100
#define INF  1<<30

int ShortestPath_spfa(int G[][MAXN], int vexnum, int v0, int *P, int *dist){
	 bool visited[MAXN];
	 int cnt[MAXN];
	 queue<int> Q;

	 memset(visited, 0, sizeof(visited));
	 memset(cnt, 0, sizeof(cnt));
	 for(int i = 0; i < vexnum; ++i)
	 	dist[i] = INF;
	
	 dist[v0] = 0;
	 Q.push(v0);
	 visited[v0] = true; 
	 cnt[v0] = 1;

	 int res = 1;
	 while(!Q.empty()){
	 	int v = Q.front();
	 	Q.pop();
	 	visited[v] = false;

	 	for(int w = 0; w < vexnum; ++w)
	 		if(G[v][w] < INF && (dist[v] + G[v][w]< dist[w])){
	 			dist[w] = dist[v] + G[v][w];
	 			P[w] = v;
	 			if(!visited[w]){
	 				visited[w] = true;
	 				cnt[w]++;
	 				Q.push(w);
	 				if(cnt[w] > vexnum)
	 					return res=0;
	 			}
	 		}
	 }

	 return res;
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

        ShortestPath_spfa(graph, N, K, path, D);
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
