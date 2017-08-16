#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

vector<int> FindNumbersWithSum(vector<int> array, int sum){
	int i = 0, j = array.size()-1;
	vector<int> res;

	while(i < j){
		if(array[i] + array[j] == sum){
			cout << array[i] << ", " << array[j] << endl;
			res.push_back(array[i]*array[j]);
			++i;
			--j;
		}else if(array[i] + array[j] > sum){
			--j;
		}else{
			++i;
		}

	}

	return res;
}

int main(){
	int n, sum;
	fstream fin("./input/input42");

	while(fin >> n >> sum){
		vector<int> vec(n);
		for(int i = 0; i < n; ++i)
			fin >> vec[i];

		FindNumbersWithSum(vec, sum);

	}
	return 0;
}