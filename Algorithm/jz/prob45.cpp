#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

bool IsContinuous(vector<int> numbers ) {
	if(numbers.size() != 5)
		return false;
    
    sort(numbers.begin(), numbers.end());

    int count = 0;
    while(numbers[count] == 0)
    	count++;

    for(int i = count+1; i < 5; ++i){
    	if(numbers[i] == numbers[i-1])
    		return false;
    }
    	
    if(numbers[4] - numbers[count] <= 4)
    	return true;

    return false;
}

int main(){
	int n;
	fstream fin("./input/input45");

	while(fin >> n){
		vector<int> num(n);
		for(int i = 0; i < n; ++i)
			fin >> num[i];

		if(IsContinuous(num)){
			cout << "Yes\n";
		}else{
			cout << "No\n";
		}
	}
	return 0;
}