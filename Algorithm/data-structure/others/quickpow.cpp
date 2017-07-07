#include <iostream>
#include <cstring>
using namespace std;

#define MOD 10007
#define MAXN 3

struct matrix{
    int a[MAXN][MAXN];
    int len;
    matrix(int n) : len(n) {
        for(int i = 0; i < len; ++i)
            for(int j = 0; j < len; ++j)
                a[i][j] = 0;
    }
    matrix(int _a[][MAXN], int n) : len(n){
        for(int i = 0; i < MAXN; ++i)
          for(int j = 0; j < MAXN; ++j)
            a[i][j] = _a[i][j]; 
    }
    void init(){
        for(int i = 0; i < len; ++i)
              a[i][i] = 1;
    }
};

// Calculate x^n 1
int qpow1(int x, int n){
    int res = 1;
    
    x = x % MOD;
    while(n){
        if( n % 2){
            res = (res * x) % MOD;           
        }
        x = (x * x) % MOD;
        n = n / 2;
    }
    return res;

}

// Calculate x^n 2
int qpow2(int x, int n){
    int res = 1;

    x = x % MOD;
    while(n){
        if(n & 1){
            res = (res * x) % MOD;
        }
        x = (x * x) % MOD;
        n >>= 1;
    }
    return res;
}

// Display Array 
void show_array(int a[][MAXN], int len){
    for(int i = 0; i < len; ++i){
      for(int j = 0; j < len; ++j)
          cout << a[i][j] << " ";
      cout << endl;
    }
}

// Display Array
void show_array1(matrix mtx){
    for(int i = 0; i < mtx.len; ++i){
      for(int j = 0; j < mtx.len; ++j)
          cout << mtx.a[i][j] << " ";
      cout << endl;
    }
}

// Multiply Array
void array_mul(const int (*a)[MAXN], const int (*b)[MAXN], int n, int (*res)[MAXN]){

    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j){
        for(int k = 0; k < n; ++k)
            res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
      }
}

// Multiply Array
matrix array_mul1(const matrix mtx1, const matrix mtx2){

    matrix res(mtx1.len);
    for(int i = 0; i < mtx1.len; ++i)
      for(int j = 0; j < mtx1.len; ++j){
        for(int k = 0; k < mtx1.len; ++k)
            res.a[i][j] = (res.a[i][j] + mtx1.a[i][k] * mtx2.a[k][j]) % MOD;
      }
    return res;
}

// Quick pow of Array
void qpow_array(int a[][MAXN], int len, int n, int (*res)[MAXN]){
   
    int b[MAXN][MAXN];
    while(n){
        if(n % 2){
          for(int i = 0; i < len; ++i)
            for(int j = 0; j < len; ++j)                        
                b[i][j] = res[i][j];
          array_mul(b, a, len, res);
        }
        for(int i = 0; i < len; ++i)
            for(int j = 0; j < len; ++j)                        
                b[i][j] = a[i][j];
         array_mul(b, b, len, a);
        n /= 2;
    }
}

// Quick pow of Array
matrix qpow_array1(matrix a, int n){
   
    matrix res(a.len);
    res.init();
    while(n){
        if(n % 2){
          res = array_mul1(res, a);
        }
        a = array_mul1(a, a);
        n /= 2;
    }
    return res;
}

int main(int argc, char *argv[]){
    
    int n, m;
    int a[MAXN][MAXN] = { {1, 2, 3},
                    {4, 5, 6},
                    {0, 0, 0}};
    int ans[MAXN][MAXN] = { {1, 0, 0},
                      {0, 1, 0},
                      {0, 0, 1}
                    };
    // while(cin >> n >> m){
    //     cout << "qpow1: " << qpow1(n, m) << endl;    
    //     cout << "qpow2: " << qpow2(n, m) << endl;
    //     qpow_array(a, 3, m, ans);
    //     // array_mul(a, a, 3, ans);
    //     show_array(ans, 3);
    // }
    while(cin >> m){
        matrix mtx(a, 3); 
//        cout << "array multiply with class!" << endl;
        mtx = qpow_array1(mtx, m);  
        show_array1(mtx); 
        
    }                    
  
    return 0;
}
