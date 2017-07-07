#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <cstring>
using namespace std;

#define MAXN  100005

struct LNode{
    int v, w;
    LNode(int _v, int _w) : v(_v), w(_w) {}
}; 

map<int, vector<LNode> > edges;

// R表示节点在E数组中第一次出现时的下标
// E为深度优先遍历过程中遇到的节点编号
// Depth为深度优先遍历过程中遇到的节点深度
// Dist表示节点i到树根的距离
int R[MAXN], E[MAXN * 2], Depth[MAXN * 2];
int Dist[MAXN];
bool vis[MAXN];
int tot;
int dp[MAXN][20];    // RMQ 数组

/**************************************************************************
 *  LCA转RMQ预处理
 *  思路： 用深度优先遍历整棵树，记录遍历过程中的节点编号E，
 *         节点深度Depth，节点在E中第一次出现时的下标，节点
 *         到树根的距离。
 *  @param   u  节点
 *  @param   d  节点的深度
 *  @return  无返回值
 **************************************************************************
 */
void DFS(int u, int d){
    // 标记该节点已访问
    vis[u] = true;
    // 记录访问的节点以及深度
    E[++tot] = u;
    Depth[tot] = d;
    // 节点在E中第一次出现时下标
    R[u] = tot;

    // 遍历节点u的邻接点
    vector<LNode> next = edges[u];
    for(auto &t : next){
        int v = t.v;
        // 节点u的邻接点v未访问
        if(!vis[v]){ 
            // 记录节点v到根节点的距离
            Dist[v] = Dist[u] + t.w;
            // 递归访问
            DFS(v, d+1);
            // 回退回去，记录下u节点以及深度
            E[++tot] = u;
            Depth[tot] = d;
        }
    }

}

/**************************************************************************
 *  LCA RMQ预处理
 *  思路： 类似普通RMQ的预处理，区别dp[i][j]记录区间 [i, i+2^j-1]中
 *         最小值的下标
 *  @param   a[]  求最小值的数组   
 *  @param   n    数组中数的个数
 *  @return  无返回值
 *************************************************************************  
 */
void InitRMQ(const int a[], int n){
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; ++i)
        dp[i][0] = i;

    for(int j = 1; (1<<j) <= n; ++j)
       for(int i = 1; i <= n+1-(1<<j); ++i){
         int k = i + (1<<(j-1));
         dp[i][j] = (Depth[dp[i][j-1]] < Depth[dp[k][j-1]]? dp[i][j-1] : dp[k][j-1]);
       }
}

/**************************************************************************
 *  LCA RMQ 查询，返回区间[i, j]中最小值的下标
 *  @param  i  区间左边
 *  @param  j  区间右边
 *  @return  返回区间[i, j]中最小值的下标  
 **************************************************************************
 */
int RMQ(int i, int j){
    int k = (int)(log(j*1.0-i+1) / log(2.0));
    int t = j - (1<<k) + 1;
    
    return Depth[dp[i][k]] < Depth[dp[t][k]] ? dp[i][k] : dp[t][k]; 
}

/**************************************************************************
 *  LCA 找u，v的最近公共祖先
 *  @param   u  节点u
 *  @param   v  节点v
 *  @return  返回节点u，v的最近公共祖先
 **************************************************************************  
 */
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
        edges.clear();
        memset(vis, 0, sizeof(vis));
        tot = 0;

        for(int i = 0; i < N; ++i){
            int u, v, w;
            fin >> u >> v >> w;
            // 注意是临接表存储
            edges[u].push_back(LNode(v, w));
            edges[v].push_back(LNode(u, w));
        }

        DFS(1, 0);
        InitRMQ(Depth, 2*M-1);
        cin >> M;
        for(int j = 0; j < M; ++j){
            int u, v;
            cin >> u >> v;
            int lca = LCA(u, v);
            cout << u << "," << v << " LCA is " << lca;
            cout << ", Distance is " << Dist[u] + Dist[v] - Dist[lca]*2 << endl;
        }     

    }
    return 0;
}

