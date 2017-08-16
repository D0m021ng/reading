#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> multiply(const vector<int>& A) {
	int n = A.size();
           
    if(n > 1){
        vector<int> res(n);
    	res[0] = 1;
        for(int i = 1; i < n; ++i)
            res[i] = res[i-1] * A[i-1];
        
        int tmp = 1;
        for(int i = n-2; i >=0; --i){
        	tmp *= A[i+1];
            res[i] *= tmp;
        }

        for(auto t : res)
        	cout << t << " ";
        cout << endl;
        return res;
    }else{
        return A;
    }
}

int main(){
	int n;
	fstream fin("./input/input50");

	while(fin >> n){
		vector<int> num(n);
		for(int i = 0; i < n; ++i)
			fin >> num[i];

		multiply(num);
	}
	return 0;
}
