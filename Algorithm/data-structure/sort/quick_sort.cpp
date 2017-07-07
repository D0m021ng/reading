#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#define N 10001

int a[N];

void quicksort(int a[], int left, int right){

	if(left < right){
	    int key = a[left];
	    int low = left;
	    int hight = right;

	    while(low < hight){
	    	while(low < hight && a[hight] >= key){
	    		--hight;
	    	}
	    	a[low] = a[hight];

	    	while(low < hight && a[low] < key){
	    		 ++low;
	    	}
	    	a[hight] = a[low];
	    }
	    a[low] = key;
	    quicksort(a, left, low-1);
	    quicksort(a, low+1, right);
	}
}

int main(){

    int n;
    fstream fin("input");
    while(fin >> n){

        for(int i = 0; i < n; ++i){
            fin >> a[i];
        }
        cout << "Number of array element: " << n << endl;
        quicksort(a, 0, n-1);

        for(int i = 0; i < n; ++i){
            cout << a[i] << " ";
        }
        cout << endl << " END! \n";
    
    }
    return 0;
}
