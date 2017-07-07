#include <iostream>
#include <map>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN 10010

struct LNode{
    int v, w;
    LNode(int _v, int _w) : v(_v), w(_w) {}
}; 

map<int, vector<LNode> > edges;

int timeStamp;
int tbegin[MAXN], tend[MAXN];
long long timeFromRoot[MAXN];

void dfs(int rt, long long time){

	timeFromRoot[rt] = time;
	tbegin[rt] = timeStamp++;
	
	vector<LNode> LN = edges[rt];
	for(auto &t : LN){
		dfs(t.v, time + t.w);
	}
	tend[rt] = timeStamp++;

}

int main(int argc, char* argv[]){
	
	int N, M;
    while(cin >> N >> M){

        for(int i = 1; i < N; ++i){
            int a, b, t;
            cin >> a >> b >> t;
            edges[a].push_back(LNode(b, t));
        }

        timeStamp = 0;
        memset(tbegin, 0, sizeof(tbegin));
        memset(tend, 0, sizeof(tend));
        memset(timeFromRoot, 0, sizeof(timeFromRoot));
      	dfs(1, 0);

      	long long seg = 0;
      	long long time = 0;
      	for(int j = 0; j < M; ++j){
            int u, v;
            cin >> u >> v;
            if(tbegin[u] <= tbegin[v] && tend[u] >= tend[v]){
            	seg++;
 				time += (long long)(timeFromRoot[v] - timeFromRoot[u]);
            }
        }  
        cout << seg << endl << time << endl;   
    }

	return 0;
}
