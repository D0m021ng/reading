#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define MAXN 5005
char mp[MAXN][MAXN];
char amp[MAXN];
int vis[MAXN][MAXN];
int step[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool DFS(char* matrix, int sx, int sy, int rows, int cols, char* str, int *vis){
	if(*str == '\0')
        return true;
    
    for(int i = 0; i < 4; ++i){
        int gx = sx + step[i][0];
        int gy = sy + step[i][1];
        
        if(gx >= 0 && gx < rows && gy >= 0 && gy < cols && !vis[gx*cols+gy] && matrix[gx*cols+gy] == *str){
            vis[gx*cols+gy] = 1;
            if(DFS(matrix, gx, gy, rows, cols, str+1, vis))
                return true;
            vis[gx*cols+gy] = 0;
        }
    }

    return false;
}

bool hasPath(char* matrix, int rows, int cols, char* str){

	if(matrix == nullptr || rows < 1 || cols < 1 || str == nullptr)
		return false;

	int *vis = new int[rows*cols]();
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j){
            if(matrix[i*cols+j] == *str){
                vis[i*cols+j] = 1;
                if(DFS(matrix, i, j, rows, cols, str+1, vis)){
                	delete[] vis;
                    return true;
                }
                vis[i*cols+j] = 0;
            }
        }

	delete[] vis;        
    return false;
}


bool DFS1(int sx, int sy, int rows, int cols, char* str){

	if(*str == '\0'){
		return true;
	}

	for(int i = 0; i < 4; ++i){
			int gx = sx + step[i][0], gy = sy + step[i][1];

			if(gx >= 0 && gx < rows && gy >= 0 && gy < cols && !vis[gx][gy] && mp[gx][gy] == *str){
				// cout << "DFS: x = " << gx << ", y = " << gy << endl;
				vis[gx][gy] = 1;
				if(DFS1(gx, gy, rows, cols, str+1))
					return true;
				vis[gx][gy] = 0;
			}

		}

	return false;
}

bool hasPath1(int rows, int cols, char* str){

	memset(vis, 0, sizeof(vis));
	for(int i = 0; i < rows; ++i)
		for(int j = 0; j < cols; ++j){
			if(mp[i][j] == *str){
				vis[i][j] = 1;
				// cout << "hasPath: x = " << i << ", y = " << j << endl;
				if(DFS1(i, j, rows, cols, str+1))
					return true;
				vis[i][j] = 0;
			}
		}

	return false;		
}

int main(){
	int n, m, k;
	fstream fin("./input/input65");

	while(fin >> n >> m){
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				fin >> amp[i*m+j];

		char str[55];
		fin >> k;
		for(int i = 0; i < k; ++i){
 			fin >> str;

			if(hasPath(amp, n, m, str)){
				cout << "True" << endl;
			}else{
				cout << "False" << endl;
			}	
		}		
	}

	return 0;
}