#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

#define MAXN 1001

struct Goods{
    int cost, weight, quantum;
    Goods(int _c, int _w, int _q=1) : cost(_c), weight(_w), quantum(_q) {}
};

int dp[MAXN], used[MAXN];
int F[MAXN][MAXN];

void show_path(vector<Goods> G, int V){
 
    memset(used, 0, sizeof(used));
    for(int i = G.size(); i > 0; --i)
        if(F[i][V] != F[i-1][V]){
            used[i] = 1;
            V -= G[i-1].cost;
        }

    cout << "Print Goods : ";
    for(int i = 1; i <= G.size(); ++i)
        if(used[i])
            cout << G[i-1].weight << " ";
    cout << endl;

}

/************************************************************************
 *  01背包问题：有N种物品和一个容量为V的背包，每种物品只有一件可用，
 *      第i种物品耗费的空间是Ci，价值是Wi。求装入那些物品，耗费空间不超过
 *      背包容量且价值总和最大。
 *  方法一： 使用二维数组F[i, v]，表示前i件物品恰放入一个容量为v的背包，
 *      可以获得的最大价值。状态转移方程：
 *      F[i, v] = max{F[i-1, v], F[i-1, v-Ci]+Wi}
 *  @param G 需要放入背包中的物品
 *  @param V 背包容量
 *************************************************************************  
 */
int Knapsack_01_Way1(vector<Goods> G, int V){

    memset(F, 0, sizeof(F));

    for(int i = 1; i <= G.size(); ++i){
        Goods t = G[i-1];
        for(int j = t.cost; j <= V; ++j){
            int k = F[i-1][j-t.cost] + t.weight;
            F[i][j] = F[i-1][j] > k ? F[i-1][j] : k;
        }
    }
    show_path(G, V);
    return F[G.size()][V];
}

/************************************************************************
 *  01背包问题：有N种物品和一个容量为V的背包，每种物品只有一件可用，
 *      第i种物品耗费的空间是Ci，价值是Wi。求装入那些物品，耗费空间不超过
 *      背包容量且价值总和最大。
 *  方法一： 使用二维数组F[i, v]，表示前i件物品恰放入一个容量为v的背包，
 *      可以获得的最大价值。状态转移方程：
 *      F[i, v] = max{F[i-1, v], F[i-1, v-Ci]+Wi}
 *  方法二： 优化方案，使用一维数组表示状态转移方程
 *      F[v] = max{F[v], F[v-Ci]+Wi}
 *      第二重循环从V到Ci
 *  @param G 需要放入背包中的物品
 *  @param V 背包容量
 *************************************************************************  
 */
int Knapsack_01(vector<Goods> G, int V){

    memset(dp, 0, sizeof(dp));

    for(int i = 0; i < G.size(); ++i){
        Goods t = G[i];
        for(int j = V; j >= t.cost; --j){
            dp[j] = dp[j] > (dp[j-t.cost] + t.weight) ? dp[j] : (dp[j-t.cost] + t.weight);
        }

    }

    return dp[V];
}

/*************************************************************************
 *  完全背包问题：有N种物品和一个容量为V的背包，每种物品都有无限件可用，
 *      第i种物品耗费的空间是Ci，价值是Wi。求装入那些物品，耗费空间不超过
 *      背包容量且价值总和最大。
 *  使用一维数组表示状态转移方程，F[v] = max(F[v], F[v-Ci]+Wi)
 *  @param G 需要放入背包中的物品
 *  @param V 背包容量
 ************************************************************************* 
 */
int Knapsack_Complete(vector<Goods> G, int V){
    
    memset(dp, 0, sizeof(dp));

    for(int i = 0; i < G.size(); ++i){
        Goods t = G[i];
        for(int j = t.cost; j <= V; ++j){
            dp[j] = dp[j] > (dp[j-t.cost] + t.weight) ? dp[j] : (dp[j-t.cost] + t.weight);
        }

    }
    return dp[V];
}

/*************************************************************************
 *  多重背包问题：有N种物品和一个容量为V的背包，第i种物品最多有Mi件可用，
 *      每件耗费的空间是Ci，价值是Wi。求装入那些物品，耗费空间不超过背包
 *      容量且价值总和最大。
 *  方法一： 使用二维数组表示状态转移方程
 *    F[i，v] = max{F[i-1, v-k*Ci]+k*Wi | 0<=k<=Mi }
 *  方法二： 转化为01背包问题
 *    将第i件物品换成logMi+1件对应的01背包物品，
 *    物品的费用和价值乘以系数：1, 2, 2^2, Mi-2^k+1，且k是满足Mi-2^k+1>0
 *    的最大整数
 *  @param G 需要放入背包中的物品
 *  @param V 背包容量
 ************************************************************************* 
 */
int Knapsack_Multiple(vector<Goods> G, int V){
    vector<Goods> Good;
    // 将Mi件编号为i的物品，换成logMi+1件对应的01背包物品
    for(auto &t : G){
       int lg = (int)(log(t.quantum+1)/log(2.0)); 
       int k;
       for(int i = 0; i < lg; ++i){
           k = 1<<i;
           Good.push_back(Goods(k*t.cost, k*t.weight));
       }

       k = t.quantum + 1 - (1<<lg);
       if(k > 0){
        Good.push_back(Goods(k*t.cost, k*t.weight));
       }
    }

    return Knapsack_01(Good, V);
}

int main(int argc, char* argv[]){
    
    int n, v;
    vector<Goods> Good;
    fstream fin("input");
    while(fin >> n >> v){
        Good.clear();
        for(int i = 0; i < n; ++i){
            int c, w, q;
            fin >> c >> w >> q;
            Good.push_back(Goods(c, w, q));
        }
        cout << "01       Knapsack: " << Knapsack_01(Good, v) << endl;
        cout << "Complete Knapsack: " << Knapsack_Complete(Good, v) << endl;     
        cout << "Multiple Knapsack: " << Knapsack_Multiple(Good, v) << endl;
        // cout << "" << v << endl;
        
    }
    return 0;
}

