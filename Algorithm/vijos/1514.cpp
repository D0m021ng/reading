#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define MAXN 200005

int A[MAXN], dpmax[MAXN][20];

// RMQ Init
void InitRMQ(const int a[], int n){
     memset(dpmax, 0, sizeof(dpmax));
     for(int i = 1; i <= n; ++i)
         dpmax[i][0] = a[i];

     int Lg = log(n) / log(2);
     for(int j = 1; j <= Lg; ++j)
         for(int i = 1; i <= n+1-(1<<j); ++i){
           int k = i + (1 << (j-1));
           dpmax[i][j] = dpmax[i][j-1] > dpmax[k][j-1] ? dpmax[i][j-1] : dpmax[k][j-1];
         }        
}

int RMQ(int i, int j){
    int k = log(j-i+1) / log(2);
    int t = j + 1 - (1<<k);
    
    return dpmax[i][k] > dpmax[t][k] ? dpmax[i][k] : dpmax[t][k];
}

int main(int argc, char* argv[]){

    int N, M;
    while(cin >> N){
        memset(A, 0 , sizeof(A));
        for(int i = 1; i <= N; ++i)
            cin >> A[i];
        InitRMQ(A, N);
        cin >> M;
        int a, b;
        for(int i = 0; i < M; ++i){
            cin >> a >> b;
            cout << RMQ(a, b) << endl;
        }
    }
    return 0;
}

