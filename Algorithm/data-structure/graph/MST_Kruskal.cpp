#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 100

// 并查集实现
int parent[MAXN];

// 并查集的初始化
void Init(int n){
	for(int i = 0; i < n; ++i)
		parent[i] = i;
}

// 并查集查询操作，注意递归过程中的状态压缩
int Find(int x){
	if(x != parent[x])
		parent[x] = Find(parent[x]);
	return parent[x];
}

// 并查集合并操作
void Union(int x, int y){
	int u = Find(x);
	int v = Find(y);
	if(u == v)
		return;
	parent[u] = v;
}

// 最小生成树 Kruskal算法
struct Edge{
	int u, v;    // 边的两个顶点
	int weight;  // 边的权值
}edge[MAXN*MAXN];

// 排序算法比较算子
bool cmp(const Edge &e1, const Edge &e2){
	return e1.weight < e2.weight;
}

/**
 *  最小生成树 Kruskal算法，C++代码实现
 *  前置条件：头文件algorithm.h 、并查集、边的集合、排序算法比较算子
 *	@param  En  图中边的数目
 *  @param  Vn  图中顶点的数组
 *  @param  Mst 记录最小生成树的边
 *  @return 得到最小生成树，返回权值；否则，返回-1
 */
int MiniSpanTree_Kruskal(int En, int Vn, vector<Edge> &Mst){
	// cost记录生成树的权值，te记录生成树的边数
	int cost = 0, te = 0;
	// 将图中的边按照从小到大排列
	sort(edge, edge+En, cmp);
	// 初始化含有Vn个顶点的并查集
	Init(Vn);
	
	// 按照从小到大的顺序遍历边集合
	for(int i = 0; i < En; ++i){
	    // 取该边的两个顶点u, v
		int u = edge[i].u;
		int v = edge[i].v;
		
		// 如果两个顶点不在同一个连通分量，则合并两个连通分量
		if(Find(u) != Find(v)){
			// 记录生成树的权值
			cost += edge[i].weight;
			// 生成树的边数加1
			te++;
			// 合并两个连通分量
			Union(u, v);
			// 将边添加到最小生成树，边集合中
			Mst.push_back(edge[i]);
		
			// 如果生成树的边数等于Vn-1，则表示最小生成树已经出现，并返回生成树权值
			if(te == Vn - 1){
				return cost;				
			}
		}
	}
	
	// 如果不存在最小生成树，则返回-1，
 	return -1;
}

int main(int argc, char *argv[]){

	int e, n, u, v, w;

	ifstream fin("input_mst");
	while(fin >> e >> n){
		for(int i = 0; i < e; ++i){
			fin >> u >> v >> w;
			edge[i].u = u;
			edge[i].v = v;
			edge[i].weight = w;
		}
		vector<Edge> MST;
		int cost = MiniSpanTree_Kruskal(e, n, MST);
		cout << "Minimum Cost: " << cost << endl;
		for(auto &ed : MST){
			cout <<"u=" << ed.u << ", v=" << ed.v <<", w=" << ed.weight << endl;
		}

	}
	return 0;
}
