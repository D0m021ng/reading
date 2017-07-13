#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 1505
#define INF 100000000

int dp[MAXN][3], indeg[MAXN], a[MAXN];
vector<int> vec[MAXN];

/*******************************************************************************
 *  树形动态规划： 对一颗树上所有节点进行守卫，相邻节点可以覆盖，求最小代价
 *  思路：对于节点i的守卫情况，有3种情况： 0表示自守，1表示子守，2表示父守。
 *        设j为节点i的子节点，则状态方程：
 *        dp[i][0] = a[i] + ∑min(dp[j][0], dp[j][1], dp[j][2])  
 *        dp[i][1] = ∑min(dp[j][0], dp[j][1]) + min{dp[j][0]- dp[j][1]}
 *        dp[i][2] = ∑dp[j][1]
 *******************************************************************************
 */
void solve(int rt){
	
	vector<int> son = vec[rt];

	// 当该节点为叶子节点时 
	if(son.size() == 0){
		dp[rt][0] = a[rt];
		dp[rt][1] = a[rt];
		return;
	}
    
    // 非叶子节点
	dp[rt][0] = a[rt];
	dp[rt][1] = dp[rt][2] = 0;

	int m = INF;
	for(auto &t : son){
        // 深度优先遍历子节点
        solve(t);
        // 该节点自守
		dp[rt][0] += min(dp[t][0], min(dp[t][1], dp[t][2]));
        // 该节点子守
		dp[rt][1] += min(dp[t][0], dp[t][1]);
        // 该节点父守
		dp[rt][2] += dp[t][1];

        // 保证节点子守时，至少有一个子节点自守            
		if(dp[t][0]-dp[t][1] < m){
			m = dp[t][0] - dp[t][1];
		} 
	}

	if(m > 0)
		dp[rt][1] += m;
}

int main(int argc, char* argv[]){
	
	int N;
	fstream fin("input_1144");

	while(fin >> N){
		memset(indeg, 0, sizeof(indeg));

		for(int i = 1; i <= N; ++i){
			int id, cost, m, t;
			fin >> id >> cost >> m;

			a[id] = cost;

			vec[id].clear();
			for(int j = 0; j < m; ++j){
				fin >> t;
				indeg[t]++;
				vec[id].push_back(t);
			}

		}

		int root = 1;
		for(int i = 1; i <= N; ++i)
			if(indeg[i] == 0){
				root = i;
				break;
			}

		solve(root);
		cout << min(dp[root][0], dp[root][1])<< endl;
	}

	return 0;
}
