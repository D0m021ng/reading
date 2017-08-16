#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
 
string LeftRotateString(string str, int n) {
    string res("");

    if(!str.empty() && n >= 0 && n <= str.size()){
    	for(int i = n; i < str.size(); ++i)
    		res += str[i];
	    for(int i = 0; i < n; ++i)
	    	res += str[i];
    }
  
    cout << res << endl;
    return res;
} 

int main(){
	string st;
	int n;
	fstream fin("./input/input43");

	while(fin >> st >> n){
		LeftRotateString(st, n);				
	}
	return 0;
}
