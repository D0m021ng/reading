#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int solve(int n){
	return 0;
}

int maxCutting(int length){
	if(length < 2)
		return 0;
	
	if(length == 2)
		return 1;

	if(length == 3)
		return 3;

	int times3 = length / 3;
	if(length % 3 == 1)
		--times3;

	int times2 = (length - times3 * 3) / 2;

	return ((int)pow(3, times3)) * ((int)pow(2, times2));
}

int main(){

	int n;
	fstream fin("./input/input00");
	while(fin >> n){
		cout << maxCutting(n) << endl;
	}

	return 0;
}