#include <iostream>
#include <cstring>
using namespace std;

#define MOD 1000000007
#define MAXN 1005
#define MAXM 10005
long long dp[MAXN][MAXM];

/**
 * 问题：计算由1, 2, ..., n组成的序列中逆序数为m的序列个数
 * 方法：根据逆序数的规律，序列每增加一个数（此时长度为i），逆序数增加0～i-1。
 *       定义dp[i][j]表示长度为i的序列，逆序数是j时，序列个数。
 *       则递推公式为： dp[i][j] = dp[i][j] + dp[i-1][k], (j-i+1 <= k <= j)
 *       又因为： dp[i][j] - dp[i][j-1] = dp[i-1][j] - dp[i-1][j-i]
 *       所以：  dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-i]
 */
void calc(){
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i < MAXN; ++i)
        dp[i][0] = 1;

    for(int i = 2; i < MAXN; ++i)
        for(int j = 1; j < MAXM; ++j){
            if(j >= i)
                dp[i][j] = (dp[i][j] + dp[i][j-1] + dp[i-1][j] - dp[i-1][j-i] + MOD) % MOD;
            else
                dp[i][j] = (dp[i][j] + dp[i][j-1] + dp[i-1][j]) % MOD;
        }
}

long long quickpow(long long n, long long p){
    long long res = 1;

    while(p){
        if(p & 1)
            res = (res * n) % MOD;
        n = (n * n) % MOD;
        p >>= 1;
    }
    return res;
}

int main(){
    
    int n, m;

    calc();
    while(cin >> n >> m){
       cout << quickpow(2ll, dp[n][m]) << endl; 
    }
    return 0;
}
