#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int LastRemaining_Solution(int n, int m){
	if(n < 1 && m < 1)
		return -1;

	int last = 0;
	for(int i = 2; i <= n; i++)
		last = (last + m) % i;

	return last;	
} 

int LastRemaining_Solution1(int n, int m){
	if(n < 1 && m < 1)
		return -1;

   	int *a = new int[n];
   	for(int i = 0; i < n; ++i)
   		a[i] = i;

   	int size = n, j = 0, t, pre = 0;
   	while(size > 1){

   		t = 0;
   		while(j < n && t < m){
   			if(a[j] == j)
   				++t;
   			pre = j;
   			j = (j+1) % n;
   		}
   		
   		a[pre] = -1;
   		
   		size = 0;
   		for(int i = 0; i < n; ++i)
   			if(a[i] == i)
   				size++;
   	}

   	t = 0;
   	for(int i = 0; i < n; ++i)
   		if(a[i] == i){
   			t = i;
   			break;
   		}

   	delete[] a;
	return t;   		
} 

int main(){
	int n, m;
	fstream fin("./input/input46");

	while(fin >> n >> m){
		cout << LastRemaining_Solution1(n, m) << endl;
	}
	return 0;
}
