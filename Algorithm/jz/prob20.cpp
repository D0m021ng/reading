#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> printMatrix(vector<vector<int> > matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();
           
    vector<int> res;
   	int rows_s = 0, cols_s = 0, i;

   	while(rows_s < rows && cols_s < cols){
   		for(i = cols_s; i < cols; ++i){
   			// cout << matrix[rows_s][i] << " ";
   			res.push_back(matrix[rows_s][i]);
   		}
   		cols--;
   		

   		for(i = rows_s+1; i < rows; ++i){
   			// cout << matrix[i][cols] << " ";
   			res.push_back(matrix[i][cols]);
   		}
   		rows--;

   		for(i = cols-1; rows > rows_s && i >= cols_s; --i){
   			// cout << matrix[rows][i] << " ";
   			res.push_back(matrix[rows][i]);
   		}
   		rows_s++;

   		for(i = rows-1; cols > cols_s && i >= rows_s; --i){
   			// cout << matrix[i][cols_s] << " ";
   			res.push_back(matrix[i][cols_s]);
   		}
   		cols_s++;
   	}

   	return res;
}

int main(){
	int n, m;
	fstream fin("./input/input20");

	while(fin >> n >> m){
		vector<vector<int> >  vec(n, vector<int>(m));
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				fin >> vec[i][j];

		printMatrix(vec);	
		cout << endl;		
	}
	return 0;
}