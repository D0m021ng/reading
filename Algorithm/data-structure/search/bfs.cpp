#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <iostream>
using namespace std;
#define N 5555

struct Node{
    int x, step;
    string path;
};

int n, k, m;
int vis[N];

bool Isok(int x){
    return (x%k+k)%k == ((n+1)%k+k)%k;
}

bool bfs(){
    memset(vis, 0, sizeof(vis));
    queue<Node> Q;
    Node p,q;
    p.x = n, p.step = 0, p.path = "";
    vis[(p.x%k+k)%k] = true;
    Q.push(p);

    while(!Q.empty()){
        p = Q.front();
        Q.pop();

        if(Isok(p.x)){
            cout << p.step << endl;
            cout << p.path << endl;
            return true;
        }
        
        q.step = p.step + 1;
        for(int i = 0; i < 4; ++i){
            switch(i){
                case 0: { 
                          q.x = ((p.x+m)%(k*m) + k*m) % (k*m);
                          q.path = p.path + '+';
                          break;
                        }
                case 1: { 
                          q.x = ((p.x-m)%(k*m) + k*m) % (k*m);
                          q.path = p.path + '-';
                          break;
                        }
                case 2: {
                          q.x = ((p.x*m)%(k*m) + k*m) % (k*m);
                          q.path = p.path + '*';
                          break;
                        }
                case 3: {
                          q.x = (p.x%m + m) % m;
                          q.path = p.path + '%';
                          break;
                        }
            }
            if(!vis[(q.x%k+k)%k]){
                vis[(q.x%k+k)%k] = true;
                Q.push(q);
            }

        }
    }
    return false;
}

int main(){

    while(scanf("%d %d %d", &n, &k, &m), n||k||m){
        if(!bfs()){
            puts("0");
        }
    }
    return 0;
}

