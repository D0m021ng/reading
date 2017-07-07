#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

#define MAXN  100005

struct Edge{
    int from, to, w, next;
};

struct Edge edges[MAXN];

// 邻接表表头
int head[MAXN];
// R表示节点在E数组中第一次出现时的下标
// E为深度优先遍历过程中遇到的节点编号
// Depth为深度优先遍历过程中遇到的节点深度
// Dist表示节点到根节点的路徑长度
int R[MAXN], E[MAXN * 2], Depth[MAXN * 2], Dist[MAXN];
int dp[MAXN][20];    // RMQ 数组
bool vis[MAXN];
int tot, cnt;

void insert(int a, int b, int c){
    edges[cnt].from = a;
    edges[cnt].to = b;
    edges[cnt].w = c;
    edges[cnt].next = head[a];
    head[a] = cnt++;
}

void DFS(int u, int d){
    vis[u] = true;
    E[++tot] = u;
    R[u] = tot;
    Depth[tot] = d;
    for(int i = head[u]; i != -1; i = edges[i].next){
        int v = edges[i].to;
        if(!vis[v]){
            Dist[v] = Dist[u] + edges[i].w;
            DFS(v, d+1);
            E[++tot] = u;
            Depth[tot] = d;
        }
    }
}

void InitRMQ(const int a[], int n){
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; ++i)
        dp[i][0] = i;

    for(int j = 1; (1<<j) <= n; ++j)
       for(int i = 1; i <= n+1-(1<<j); ++i){
         int k = i + (1<<(j-1));
         dp[i][j] = a[dp[i][j-1]] < a[dp[k][j-1]]? dp[i][j-1] : dp[k][j-1];
       }
}

int RMQ(int i, int j){
    int k = (int)(log(j*1.0-i+1) / log(2.0));
    int t = j - (1<<k) + 1;

    return Depth[dp[i][k]] < Depth[dp[t][k]] ? dp[i][k] : dp[t][k];
}


int LCA(int u, int v){
    int res;
    if(R[u] < R[v]){
        res =  RMQ(R[u], R[v]);
    }else{
        res =  RMQ(R[v], R[u]);
    }
    return E[res];
}

int main(int argc, char* argv[]){

    int N, M;
    fstream fin("input_lca");
    while(fin >> N >> M){

        memset(head, -1, sizeof(head));
        memset(vis, 0, sizeof(vis));
        tot = 0;
        cnt = 0;

        for(int i = 0; i < N; ++i){
            int u, v, w;
            fin >> u >> v >> w;
            insert(u, v, w);
            insert(v, u, w);
        }

        DFS(1, 0);
        InitRMQ(Depth, 2*M-1);
        cin >> M;
        for(int j = 0; j < M; ++j){
            int u,v;
            cin >> u >> v;
            int lca = LCA(u ,v);
            cout << u << "," << v << " LCA is " << lca;

            cout << ", Distance is " << Dist[u] + Dist[v] - Dist[lca]*2 << endl;
        }     

    }
    return 0;
}

