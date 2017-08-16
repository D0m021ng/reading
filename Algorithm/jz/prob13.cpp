#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
 
void reOrderArray(vector<int> &array) {
    size_t size = array.size();
   
    if(size > 1){
    	vector<int> res;
    	for(int i = 0; i < size; ++i)
    		if(array[i] % 2){
    			res.push_back(array[i]);
    		}

	    for(int i = 0; i < size; ++i)
    		if(array[i] % 2 == 0){
    			res.push_back(array[i]);
    		}  

    	array = res;	  			
    }
} 

int main(){
	int n;
	fstream fin("./input/input13");

	while(fin >> n){
		vector<int> arr(n);
		for(int i = 0; i < n; ++i)
			fin >> arr[i];

		reOrderArray(arr);

		for(auto t : arr)
			cout << t << " ";
		cout << endl;
	}
	return 0;
}
