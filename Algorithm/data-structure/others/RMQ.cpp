#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
using namespace std;

#define MAXN 1000005
#define M 30

int A[MAXN], dp[MAXN][M];

/***************************************************************************
 *  RMQ高效在线算法（ST算法）初始化操作
 *  思路：使用动态规划，假设dp[i][j]表示从第i个数开始，连续2^j个数中最大值。
 *        初始化状态dp[i][0] = a[i]，dp[i][j]表示区间[i, i+2^j-1]中最大值，
 *        将此区间平均划分为两部分：[i, i+2^(j-1)-1]和 [i+2^(j-1), i+2^j-1]，
 *        这两个区间分别对应dp[i][j-1]和dp[i+2^(j-1)][j-1]。因此，状态转移
 *        方程为：dp[i][j] = max(dp[i][j-1], dp[i+2^(j-1)][j-1])
 *  @param  a[]   需要查询的数组
 *  @param  n     数的个数
 *  @return       无返回值
 ***************************************************************************
 */
void InitRMQ(const int a[], int n){
    // 初始化dp
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; ++i)
        dp[i][0] = a[i];
    
    // 计算j值的上限
    int Lg = log(n) / log(2);
    // 计算dp[i][j]，（1<=j<=log2(n)）
    for(int j = 1; j <= Lg; ++j){
        // 由于i+2^j <= n，所以i最大为n+1-2^j
        for(int i = 1; i <= n+1-(1<<j); ++i){
            int k = i + (1 << (j-1));
            dp[i][j] = (dp[i][j-1] > dp[k][j-1]? dp[i][j-1] : dp[k][j-1]);
        }
    }
}

/***************************************************************************
 *  RMQ高效在线算法（ST算法）查询操作
 *  思路：查询区间[i, j]中的极值，将区间平均划分为两个部分：
 *        [i, i+2^log2(j-i+1)]和[j-2^log2(j-i+1)+1, j]，则两个区间分别对应：
 *        dp[i][log2(j-i+1)]和dp[j-2^log2(j-i+1)+1][log2(j-i+1)]。只需求这
 *        两个区间上极值中最大值即可。
 *  @param  i  区间的左边       
 *  @param  j  区间的右边
 *  @return    返回区间[i, j]中最大值
 *
 *************************************************************************** 
 */
int RMQ(int i, int j){
    // 计算log2(j-i+1)
    int k = log(j-i+1) / log(2);
    int t = j - (1<<k) + 1;
    // 从子区间中选择最大者
    return dp[i][k] > dp[t][k] ? dp[i][k] : dp[t][k];
}

int main(int argc, char* argv[]){

    int n;
    fstream fin("input");
    while(fin>> n){
        memset(A, 0, sizeof(A));
        for(int i = 1; i <= n; ++i){
            fin >> A[i];
            cout << A[i] << " ";
        }
        InitRMQ(A, n);

        cin >> n;
        for(int i = 0; i < n; ++i){
            int a, b;
            cin >> a >> b;
            cout << "MAX of A[" << a <<", "<< b <<"] is "<< RMQ(a, b) << endl;
        }
    }
    return 0;
}
