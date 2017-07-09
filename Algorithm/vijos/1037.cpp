#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 105
#define MAXH 2005

int dp[MAXN][MAXH], sum[MAXN];

/***********************************************************************
 *  思路：设dp[i][j]表示前i块水晶堆成高度差为j的双塔时，较矮的塔
 *        最大高度。此时，对于第i块水晶，有2种情况，选或不选。其中，
 *        当选第i块水晶时，有3种放置情况。对于第i块水晶，高度为hi，
 *        前i块水晶高度和为s[i]，状态方程如下：
 *        1) 不选第i块水晶，则 dp[i][j] = dp[i-1][j];
 *        2) 选择第i块水晶，且放在较高的塔上，则 
 *            dp[i][j] = max(dp[i][j], dp[i-1][j-hi]), j-hi >= 0
 *        3) 选择第i块水晶，且放在较低的塔上，不改变高低关系，则
 *            dp[i][j] = max(dp[i][j], dp[i-1][j+hi]+hi), j+hi<=s[i-1]
 *        4) 选择第i块水晶，且放在较低的塔上，改变高低关系，则
 *            dp[i][j] = max(dp[i][j], dp[i-1][hi-j]+hi-j, hi-j >= 0
 ***********************************************************************
 */
void solve(vector<int> a){

    memset(dp, -0x3f, sizeof(dp));
    dp[0][0] = 0;

    int n = a.size();
    for(int i = 1; i <= n; ++i){
        int t = a[i-1];
        for(int j = 0; j <= sum[i]; ++j){
            // 不选第i块水晶
            dp[i][j] = dp[i-1][j];

            // 选择第i块水晶，且放在较高的塔上
            if(j-t >= 0 && dp[i-1][j-t] > dp[i][j]){
                dp[i][j] = dp[i-1][j-t];
            }

            // 选择第i块水晶，且放在较低的塔上，不改变高低关系
            if(j+t <= sum[i-1] && dp[i-1][j+t]+t > dp[i][j]){
                dp[i][j] = dp[i-1][j+t] + t;
            }

            // 选择第i块水晶，且放在较低的塔上，改变高低关系
            if(t-j >= 0 && dp[i-1][t-j]+t-j > dp[i][j]){
                dp[i][j] = dp[i-1][t-j] + t - j;
            }
        }

    }


    if(!dp[n][0]){
        cout << "Impossible" << endl;
    }else{
        cout << dp[n][0] << endl;
    }
}

int main(int argc, char* argv[]){
    
    int N;
    vector<int> crystal;

    fstream fin("input_1037");
    while(fin >> N){
       
        crystal.clear();
        memset(sum, 0, sizeof(sum));
        for(int i = 1; i <= N; ++i){
            int j;
            fin >> j;
            sum[i] = sum[i-1] + j;
            crystal.push_back(j);
        }

        solve(crystal);
    }
    

    return 0; 
}

