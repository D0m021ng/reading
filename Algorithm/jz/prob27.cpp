#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void Permuta(string str, int n, int length, vector<string> &res){

	if(n == length-1){
		res.push_back(str);
	}else{
		for(int i = n; i < length; ++i){

			if(i != n && str[i] == str[n])
				continue;
			swap(str[i], str[n]);
			Permuta(str, n+1, length, res);
			swap(str[i], str[n]);
		}
	}
}

vector<string> Permutation(string str) {
	vector<string> res;

	if(str == "")
		return res;

	Permuta(str, 0, str.size(), res);
	sort(res.begin(), res.end());

	for(auto t : res)
		cout << t << endl;
	cout << endl;
	return res;    
}


int main(){
	string st;
	fstream fin("./input/input44");

	while(fin >> st){
		Permutation(st);
	}
	return 0;
}
