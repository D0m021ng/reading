#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int minNumberInRotateArray(vector<int> rotateArray){

	int p1 = 0, p2 = rotateArray.size() - 1;
	int mid = p1;

	while(rotateArray[p1] >= rotateArray[p2]){
		if(p2 - p1 == 1){
			mid = p2;
			break;
		}

		mid = (p1 + p2) / 2;
		if(rotateArray[p1] == rotateArray[mid] && rotateArray[p2] == rotateArray[mid]){
			int min = rotateArray[p1];
			for(int i = p1+1; i <= p2; ++i){
				if(min > rotateArray[i])
					min = rotateArray[i];
			}
			return min;
		}

		if(rotateArray[p1] <= rotateArray[mid]){
			p1 = mid;
		}else if(rotateArray[p2] >= rotateArray[mid]){
			p2 = mid;
		}
	}

	return rotateArray[mid];
}

int minNumberInRotateArray1(vector<int> rotateArray){

	int p1 = 0, p2 = rotateArray.size() - 1;

	if(rotateArray[p1] < rotateArray[p2]){
		return rotateArray[p1];
	}

	while( p1 + 1 != p2 ){
		int mid = (p1 + p2) / 2;
		if(rotateArray[p1] == rotateArray[mid] && rotateArray[p2] == rotateArray[mid]){
			int min = rotateArray[p1];
			for(int i = p1+1; i <= p2; ++i){
				if(min > rotateArray[i])
					min = rotateArray[i];
			}
			return min;
		}

		if(rotateArray[p1] <= rotateArray[mid]){
			p1 = mid;
		}else if(rotateArray[p2] >= rotateArray[mid]){
			p2 = mid;
		}
	}
	return rotateArray[p2];
}

int main(){
	int n;
	fstream fin("./input/input08");
	
	while(fin >> n){
		
		vector<int> array;
		for(int x, i = 0; i < n; ++i){
			fin >> x;
			array.push_back(x);
		}

		cout << minNumberInRotateArray(array) << ", ";
		cout << minNumberInRotateArray1(array) << endl;
	}

	return 0;	
}