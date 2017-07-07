#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

#define MAXN  100010

struct LNode{
    int v, w;
    LNode(int _v, int _w) : v(_v), w(_w) {}
}; 

map<int, vector<LNode> > edges;

// R表示节点在E数组中第一次出现时的下标
// E为深度优先遍历过程中遇到的节点编号
// Depth为深度优先遍历过程中遇到的节点深度
int R[MAXN], E[MAXN * 2], Depth[MAXN * 2];
// 保存每个点到树根的距离
int Dist[MAXN];
int dp[MAXN][20];    // RMQ 数组
bool vis[MAXN];
int tot, cnt;

void DFS(int u, int d){
    vis[u] = true;
    E[++tot] = u;
    R[u] = tot;
    Depth[tot] = d;

    vector<LNode> LN = edges[u];
    for(auto &t : LN){
        int v = t.v;
        if(!vis[v]){
        	Dist[v] = Dist[u] + t.w;
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
         dp[i][j] = (a[dp[i][j-1]] < a[dp[k][j-1]]? dp[i][j-1] : dp[k][j-1]);
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

int main(int argc, char *argv[]){
    
    int N, M;
    while(cin >> N >> M){
        memset(vis, 0, sizeof(vis));
        memset(Dist, 0, sizeof(Dist));
        tot = 0;
        cnt = 0;

        for(int i = 1; i < N; ++i){
            int a, b, t;
            cin >> a >> b >> t;
            edges[a].push_back(LNode(b, t));
            edges[b].push_back(LNode(a, t));
        }

        DFS(1, 0);
        InitRMQ(Depth, 2*N-1);

        long long  seg = 0;
        long long time = 0;
        for(int j = 0; j < M; ++j){
            int u,v;
            cin >> u >> v;
            if(LCA(u, v) == u){
            	seg++;
 				time += (long long)(Dist[v] - Dist[u]);
            }
        }     
        cout << seg << endl;
        cout << time << endl;

    }
    return 0;
}
