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

    while(cin >> C >> W >> N){

        Good.clear();
        for(int i = 0; i < N; ++i){
            int v, u, w;
            cin >> v >> u >> w;
            Good.push_back(Goods(v, u, w));
        }

        cout << TwoDimen_Knapsack(Good, C, W) << endl;        
    }
    return 0;
}

