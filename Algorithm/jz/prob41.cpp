#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
 
vector<vector<int> > FindContinuousSequence(int sum){
	
	vector<vector<int> > res;

	if(sum < 3)
		return res;
	
	int small = 1, big = 2;

	while(small < (1+sum)/2){
		int s = (small+big)*(big-small+1)/2;

		if(s == sum){
			vector<int> vec;
			for(int i = small; i <= big; ++i){
				cout << i << " ";
				vec.push_back(i);
			}
			cout << endl;
			res.push_back(vec);
			++big;
		}else if( s < sum){
			++big;
		}else{
			++small;
		}
	}

	return res;
}

int main(){
	int n;
	fstream fin("./input/input41");

	while(fin >> n){
		FindContinuousSequence(n);
	}
	return 0;
}
