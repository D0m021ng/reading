#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 10010
#define MAXM 20

struct LNode{
    int v, w;
    LNode(int _v, int _w) : v(_v), w(_w) {}
};

// 邻接表记录节点的子节点
map<int, vector<LNode> > edges;
// 记录节点的2^j倍祖先和深度
int parent[MAXN][MAXM+1], Depth[MAXN];
// 记录节点和祖先节点距离
int dist[MAXN][MAXM+1];  


/******************************************************************
 *  倍增法初始化，求节点深度和节点的2^j倍祖先
 *  思路： 设parent[i][j]表示节点i的2^j倍祖先，则可以得到递推
 *         公式：parent[i][j] = parent[parent[i][j-1]][j-1]。
 *         使用深度优先遍历，从根节点开始，记录节点i的深度和
 *         2^j倍祖先。并且记录下节点i和祖先节点的距离dist[i][j]。 
 *  @param   rt   根节点       
 *  @return  无返回值
 ******************************************************************  
 */
void DFS(int rt){
    // 当前节点深度等于父节点深度加1
    Depth[rt] = Depth[parent[rt][0]] + 1;

    // 计算当前节点的2^j倍祖先
    for(int i = 1; i <= MAXM; ++i){
        parent[rt][i] = parent[parent[rt][i-1]][i-1];
        if(!parent[rt][i])
            break;
        // 当前节点2^i倍祖先节点存在时，记录当前节点到该祖先节点距离
        dist[rt][i] = dist[parent[rt][i-1]][i-1] + dist[rt][i-1];
    }

    // 深度优先遍历当前节点的子节点
    vector<LNode> Ln = edges[rt];
    for(auto &t : Ln){
        int v = t.v;
        // 子节点未访问时
        if(!Depth[v]){
            // 设置子节点的父节点，以及子节点到父节点的距离
            parent[v][0] = rt;
            dist[v][0] = t.w;
            // 深度优先遍历子节点
            DFS(v);
        }
    }
}

/******************************************************************
 *  倍增法求节点x，y最近公共祖先以及距离
 *  思路： 将深度较高的节点y调整到与节点x同高度（x深度高时，交换x
 *         和y），然后x和y同时往上调整直到找到公共祖先。
 *  @param  x    节点x
 *  @param  y    节点y
 *  @param  ans  记录节点x和y之间距离 
 *  @param  返回节点x和y的最近公共祖先
 ******************************************************************
 */
int LCA(int x, int y, int &ans){
    // 调整x，y，保证节点x比节点y离根节点近
    if(Depth[x] > Depth[y]){
      x ^= y; y ^= x; x ^= y;
    }

    // 将节点x和y调整到同一深度
    for(int i = MAXM; i >= 0; --i)
        if(Depth[x] < Depth[y] && Depth[parent[y][i]] >= Depth[x]){
            // 记录节点y到2^i倍祖先间的距离
            ans += dist[y][i];
            // 节点y移到2^i倍祖先位置
            y = parent[y][i];
        }

    // 当节点x与节点y不等时
    if(x != y){
        // 节点x与节点y同时向上移动，找到最近公共祖先
        for(int i = MAXM; i >= 0; --i)
           if(parent[y][i] != parent[x][i]){
               // 记录节点同时上移的距离
               ans += dist[y][i] + dist[x][i];
               y = parent[y][i];   
               x = parent[x][i];
           }
        // 记录节点x、节点y到最近公共祖先的距离
        ans += dist[x][0] + dist[y][0];
        // 返回最近公共祖先
        x = parent[x][0];
    }
    return x;
}

int main(){
    int N, M;
    fstream fin("input_lca");
    while(fin >> N >> M){
        edges.clear();
        for(int i = 0; i < N; ++i){
            int u, v, w;
            fin >> u >> v >> w;
            edges[u].push_back(LNode(v, w));
            edges[v].push_back(LNode(u, w));
        }

        memset(parent, 0, sizeof(parent));
        memset(Depth, 0, sizeof(Depth));
        memset(dist, 0, sizeof(dist));
        DFS(1);

        for(int i = 1; i <= N+1; ++i){
            cout << Depth[i] << ", parent: ";
            for(int j = 0; j <= MAXM; ++j)
                cout << parent[i][j] << " ";
            cout << "\n  Distance: ";
            for(int j = 0; j <= MAXM; ++j)
                cout << dist[i][j] << " ";
            cout <<endl;
        }
        for(int j = 0; j < M; ++j){
            int u, v;
            cin >> u >> v;
            int ans = 0;
            int lca = LCA(u, v, ans);
            cout << u << "," << v << " LCA is " << lca;
            cout << ", Distance is " << ans << endl;
        }     

    }

    return 0;
}
