#include <iostream>
#include <fstream>
using namespace std;

#define MAXN 5005

// solution 1: o(n), o(n)
bool duplicate1(int numbers[], int length, int* duplication) {
        int a[5005] = {0};
        int flag = 0;
        for(int i = 0; i < length; ++i){
            a[numbers[i]]++;
            if(a[numbers[i]] == 2){
                *duplication++ = numbers[i];
                flag = 1;
            }
        }
        if(flag)
            return true;
        else
            return false;
}

// solution 2: o(n), o(1)
bool duplicate2(int numbers[], int length, int* duplication) {
    
    int flag = 0;
    for(int i = 0; i < length; ++i){
    	while(numbers[i] != i){
            if(numbers[i] == numbers[numbers[i]]){
                *duplication++ = numbers[i];
                flag = 1;
                break;
            }
            	
            int m = numbers[i];
            numbers[i] = numbers[m];
            numbers[m] = m;
		}  
    }
    if(flag)
        return true;
    else
        return false;
}


int main(){

	int array[MAXN], n, ans[MAXN];
	fstream fin("./input/input50");
    
	while(fin >> n){
		for(int i = 0; i < n; ++i)
			fin >> array[i];

		if(duplicate2(array, n, ans)){
			for(auto t = begin(ans); t != end(ans); ++t){
				if(*t == 0)
					break;
				cout << *t << " ";
			}
			cout << endl;
		}
	}
	return 0;
}