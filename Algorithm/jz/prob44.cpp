#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void ReverseWord(string &str, int s, int e){
	
	while(s < e){
		swap(str[s], str[e]);
		++s;
		--e;
	}
} 

string ReverseSentence(string str) {

	if(!str.empty()){
		auto size = str.size();
        if(size == 0) return "";
        int mark=0;
        str += ' ';
        for(int i = 0; i < size+1; ++i){
            if(str[i] == ' '){
                ReverseWord(str, mark, i-1);
                mark = i+1;
            }
        }
        str = str.substr(0, size);
        ReverseWord(str, 0, size-1);

	}
	return str;
}

int main(){
	char st[500];
	fstream fin("./input/input44");

	while(fin.getline(st, 500)){
		cout << ReverseSentence(string(st)) << endl;
	}
	return 0;
}
