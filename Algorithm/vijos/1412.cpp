#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 5005
#define MAXK 55

struct Goods{
    int costv, weight;
    Goods(int _v, int _w) : costv(_v), weight(_w) {}
};

int dp[MAXN][MAXK];
int tmp[MAXK];

/**********************************************************************
 *  归并操作，将两个有序序列归并，返回前K项
 *  @param  a  有序序列a
 *  @param  b  有序序列b
 *  @param  w  有序序列b增量
 *  @param  K  前K项
 ***********************************************************************  
 */
void merge(int a[], int b[], int w, int K){

    int i = 1, j = 1, pos = 1;

    while(i+j <= K+1){
        if(a[i] > b[j]+w){
            tmp[pos++] = a[i++];
        }else{
            tmp[pos++] = b[j++]+w;
        }
    }

    for(i = 1; i <= K; ++i)
        a[i] = tmp[i];
}

/**************************************************************************
 *  01背包K优解
 *  思路： 使用二维数组dp[i][j]表示容量为i时的第j优解，dp[i][1,..K]
 *         是一个有序序列。按照01背包解法，归并有序序列dp[i][1,..K]和
 *         有序序列dp[i-t.costw][1,..K]+t.weight，取前K项。
 *  @param  gd  物品
 *  @param  V   背包容量
 *  @param  K   K优解
 *************************************************************************  
 */
int Knapsack_K(vector<Goods> gd, int V, int K){

    memset(dp, -0x3f, sizeof(dp));
    
    dp[0][1] = 0;
    
    for(auto &t : gd)
        for(int i = V; i >= t.costv; --i){
               merge(dp[i], dp[i-t.costv], t.weight, K);            
        }

    int ans = 0;
    for(int i = 1; i <= K; ++i)
        ans += dp[V][i];        

    return ans;
}


int main(int argc, char* argv[]){
    
    int K, V, N;
    vector<Goods> gd;

    fstream fin("input_1412");
    while(fin >> K >> V >> N){

        gd.clear();
        for(int i = 0; i < N; ++i){
            int u,v;
            fin >> u >> v;
            gd.push_back(Goods(u, v));
        }

        cout << Knapsack_K(gd, V, K) << endl;
             
    }
    return 0;
}

