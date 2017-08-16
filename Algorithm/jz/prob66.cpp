#include <iostream>
#include <fstream>
using namespace std;

int step[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool Check(int x, int y, int k){
	int t = 0;
	while(x || y){
		t += x % 10 + y % 10;
		x /= 10;
		y /= 10;
	}

	if(t <= k)
		return true;
	else
		return false;
}

void DFS(int k, int sx, int sy, int rows, int cols, int *vis, int &count){

	for(int i = 0; i < 4; ++i){
		int gx = sx + step[i][0];
		int gy = sy + step[i][1];

		if(gx >= 0 && gx < rows && gy >= 0 && gy < cols && !vis[gx*cols+gy] && Check(gx, gy, k)){
			vis[gx*cols+gy] = 1;
			count++;
			DFS(k, gx, gy, rows, cols, vis, count);
		}
	}
}

int movingCount(int threshold, int rows, int cols){
	
	if(threshold < 1 || rows < 1 || cols < 1)
		return 0;
	
	int *vis = new int[rows*cols]();
	int count = 1;
	vis[0] = 1;

	DFS(threshold, 0, 0, rows, cols, vis, count);
	delete[] vis;
	return count;

}

int main(){

	int n, m, k;
	fstream fin("./input/input66");
	
	while(fin >> n >> m >> k){
		cout << movingCount(k, n, m) << endl;		
	}

	return 0;
}