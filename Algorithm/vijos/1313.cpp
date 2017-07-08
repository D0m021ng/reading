#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

#define MAXN 32005

struct Goods{
    int costv, weight, quantum;
    Goods(int _v, int _w, int _q = 0) : costv(_v), weight(_w), quantum(_q) {}
};

int dp[MAXN];

/***************************************************************************
 *  分组背包问题：每组内的物品互斥，只能选择组内一件物品或不选
 *  思路： 使用01背包的思想，每组选一件物品或不选  
 *  @param G  分组物品
 *  @param V  背包容量
 ***************************************************************************  
 */
int Knapsack_Group(vector< vector<Goods> > G, int V){
    
    memset(dp, 0, sizeof(dp));

    // 对每组物品，选一件或不选
    for(auto &vg : G){
        for(int i = V; i > 0; --i){
            for(auto &t : vg){
                if(i - t.costv >= 0 && dp[i-t.costv] + t.weight > dp[i]){
                    dp[i] = dp[i-t.costv] + t.weight;
                }
            }
        }         
    }

    return dp[V];            
}

int main(int argc, char* argv[]){
    
    int N, m;
    vector<Goods> sub;
    map<int, vector<Goods> > obj;

    fstream fin("input_1313");
    while(fin >> N >> m){

        sub.clear();
        obj.clear();
        for(int i = 1; i <= m; ++i){
            int v, p, q;
            fin >> v >> p >> q;
            if(q == 0){
                sub.push_back(Goods(v, v*p, i));
            }else{
                obj[q].push_back(Goods(v, v*p, q));
            }
        }

        vector< vector<Goods> > good;          
        
        // 将每个主件物品和附件物品，转化为一个组
        for(auto &s : sub){ 

            vector<Goods> gd, objt = obj[s.quantum];
            gd.push_back(Goods(s.costv, s.weight));

            for(auto &t : objt)
                if(t.costv + s.costv <= N)
                    gd.push_back(Goods(t.costv+s.costv, t.weight+s.weight));
            
            for(int j = 0; j < objt.size(); ++j){
                for(int k = j+1; k < objt.size(); ++k){
                    if(objt[j].costv + objt[k].costv + s.costv <= N)
                        gd.push_back(Goods(objt[j].costv + objt[k].costv + s.costv, 
                            objt[j].weight + objt[k].weight + s.weight));  
                }
            }

            good.push_back(gd);
        }

        cout << Knapsack_Group(good, N) << endl;       
    }
    return 0;
}

