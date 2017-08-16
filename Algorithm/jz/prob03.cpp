#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAXN 100
int a[MAXN][MAXN];

// bool Find(int x, int N){
// 	int i = 0, j = N-1;
	
// 	bool flag = false;
// 	while(i < N && j >= 0){
// 		if(a[i][j] == x){
// 			flag = true;
// 			break;
// 		}else if(a[i][j] < x){
// 			++i;	
// 		}else{
// 			--j;
// 		}
// 	}

// 	return flag;
// } 

bool Find(int target, vector<vector<int> > array) {
                
        bool flag = false;
        if(!array.empty()){
            
           int row = 0, col = array[0].size() - 1;
           while(row < array.size() && col >= 0){
               if(array[row][col] == target){
                   flag = true;
                   break;
               }else if(array[row][col] < target){
				   ++row;
               }else{
                   --col;
               }
           }
        }
        
        return flag;
}

int main(){

	int n, m, x;
	fstream fin("./input/input03");

	while(fin >> n >> m){
		// for(int i = 0; i < n; ++i)
		// 	for(int j = 0; j < n; ++j){
		// 		fin >> a[i][j];
		// 	}

		vector< vector<int> > array(n, vector<int>(m));

		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j){
				fin >> array[i][j];
			}
		

		while(fin >> x){
			if(Find(x, array))
				cout << "True" << endl;
			else
				cout << "False" << endl;
		}		
	}

	return 0;
}
