#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

#define N 10

bool visit[N];
int count;

// 给出序列的全排列
bool DFS(char b[], int d, const char src[], int n){
    int i;
    if(d >= n){
        count++;
        printf("%s\n", b);
    }

    for(i = 0; i < n; ++i){
        if(!visit[i]){
            visit[i] = true;
            b[d] = src[i];
            if(DFS(b, d+1, src, n)){
                return true;
            }
            visit[i] = false;
        }
    }

    return false;
}

struct Node{
    int val;
    bool visit;
};
// 非递归方式DFS
void DFS_non(const char src[], int len){
    stack<Node> N_stack;
    Node t;
    t.val = src[0];
    t.visit = true;
    printf("%c ", src[0]);
    N_stack.push(t);

    int ans = 0;
    while(!N_stack.empty()){
        char ch = N_stack.top();
        int j;    
        
        if(ans % 3 == 0){
            printf("\n");
        }

        for(j = 0; j < len; ++j){
            if(src[j] != ch && !visit[j]){
                printf("%c ", src[j]);
                ans++;
                visit[j] = true;
                N_stack.push(src[j]);
                break;
            }
        }

        if(j == len){
            N_stack.pop();
        }

    }
}

// 由给定序列组成字符串 
bool DFS_2(char b[], int d, const char src[], int n){
    int i;
    if(d >= 3){
        count++;
        printf("%s\n", b);
        return false;
    }

    for(i = 0; i < n; ++i){
        b[d] = src[i];
        if(DFS_2(b, d+1, src, n)){
                return true;
        }
    }
    
    return false;
}

int main(){

    char ans[4]="";
    char mp[10] = "+-x/";
    count = 0;
    memset(visit, 0, sizeof(visit));
    
    DFS_non(mp, strlen(mp));
//    DFS_2(ans, 0, mp, strlen(mp));
    
    printf("Total %d\n", count);
    return 0;
}
