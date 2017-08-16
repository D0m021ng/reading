#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
 


int GetUglyNumber_Solution(int index){
	
	if(index < 7)
		return index;

	vector<int> res(index);

	res[0] = 1;
	int t2 = 0, t3 = 0, t5 = 0, i;
	for(i = 1; i < index; ++i){
		res[i] = res[t2]*2 < res[t3]*3 ? res[t2]*2 : res[t3]*3;
		res[i] = res[i] < res[t5]*5 ? res[i] : res[t5]*5;

		if(res[i] == res[t2]*2)
			t2++;
		if(res[i] == res[t3]*3)
			t3++;
		if(res[i] == res[t5]*5)
			t5++;
	}
	return res[index-1];
}

int GetUglyNumber_Solution1(int index){
	vector<int> vec(index+1);

	vec[1] = 1;
	for(int i = 2; i <= index; ++i){
		int j = 1;
		while(vec[j]*2 <= vec[i-1])
			++j;
		int m2 = vec[j]*2;

		j = 1;
		while(vec[j]*3 <= vec[i-1])
			++j;
		m2 = vec[j]*3 > m2 ? m2 : vec[j]*3;

		j = 1;
		while(vec[j]*5 <= vec[i-1])
			++j;
		m2 = vec[j]*5 > m2 ? m2 : vec[j]*5;

		vec[i] = m2;
	}
	return vec[index];
}

int main(){
	int n;
	fstream fin("./input/input33");

	while(fin >> n){
		cout << GetUglyNumber_Solution(n) << endl;
	}
	return 0;
}
