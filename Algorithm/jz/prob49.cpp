#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int StrToInt(string str){
	
	if(str.size() < 1)
		return 0;

	int res = 0, i = 0;
	
	if(str[0] == '-' || str[0] == '+'){		
		i = 1;
	}

	for(; i < str.size(); ++i){
		if( str[i] >= '0' && str[i] <= '9'){
			res = res * 10 + (str[i] - '0');
		}else{
			return 0;
		}
	}

	if(str[0] == '-'){
		return -res;
	}else{
		return res;
	}
	
}

int main(){
	string st;
	fstream fin("./input/input49");
	
	while(fin >> st){
		cout << StrToInt(st) << endl;
	}

	return 0;
}