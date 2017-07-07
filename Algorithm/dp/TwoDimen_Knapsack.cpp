#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 1001

struct Goods{
    int costv, costu, weight, quantum;
    Goods(int _v, int _u, int _w, int _q=1) : costv(_v), costu(_u), weight(_w), quantum(_q) {}
};

int dp[MAXN][MAXN];

/**********************************************************************************
 *  二维背包问题：
 *  方法一： 使用三维数组dp[i, v, u]，表示前i件物品恰放入一个容量为v、最大承重
 *      为u的背包中，可以获得的最大价值。状态转移方程：
 *      dp[i, v, u] = max{dp[i-1, v, u], dp[i-1, v-Ci, u-Di]+Wi}
 *  方法二： 优化方案，使用二维数组表示状态转移方程
 *      dp[v, u] = max{dp[v, u], dp[v-Ci, u-Di]+Wi}
 *      第二重循环从V到Ci，第三重循环从U到Di
 *  param@ G  物品信息
 *  param@ V  背包花费1（容量）
 *  param@ U  背包花费2（承重）
 **********************************************************************************  
 */
int TwoDimen_Knapsack(vector<Goods> G, int V, int U){

    memset(dp, 0, sizeof(dp));

    for(int i = 0; i < G.size(); ++i){
        Goods t = G[i];
        for(int j = V; j >= t.costv; --j)
            for(int k = U; k >= t.costu; --k){
                if(dp[j-t.costv][k-t.costu] + t.weight > dp[j][k]){
                    dp[j][k] = dp[j-t.costv][k-t.costu] + t.weight;
                }
            }
    }

    return dp[V][U];
}


int main(int argc, char* argv[]){
    
    int N, C, W;
    vector<Goods> Good;
     fstream fin("input2");

    while(fin >> C >> W >> N){

        Good.clear();
        for(int i = 0; i < N; ++i){
            int v, u, w;
            fin >> v >> u >> w;
            Good.push_back(Goods(v, u, w));
        }

        cout << TwoDimen_Knapsack(Good, C, W) << endl;        
    }
    return 0;
}

