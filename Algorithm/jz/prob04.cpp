#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

#define MAXN 1000

char str[MAXN];

void replaceSpace(char* str, int length){

	if(str != NULL && length > 0){
		int space = 0;
		for(int i = 0; i < length; ++i)
			if(str[i] == ' ')
				space++;

		char *p1 = str + length - 1;
		char *p2 = p1 + 2*space;

		while(p1 != p2){
			while(*p1 != ' ')
				*p2-- = *p1--;
			if(*p1 == ' '){
				p1--;
				*p2-- = '0';
				*p2-- = '2';
				*p2-- = '%';
			}
		}
	}	
}

void replaceSpace1(char* str, int length){

	if(str != NULL && length > 0){
		int space = 0;
		for(int i = 0; i < length; ++i)
			if(str[i] == ' ')
				space++;

		int oldlen = length-1;
		int newlen = oldlen + 2*space;
		
		while(oldlen != newlen){
			while(str[oldlen] != ' ')
				str[newlen--] = str[oldlen--];

			if(str[oldlen] == ' '){
				oldlen--;
				str[newlen--] = '0';
				str[newlen--] = '2';
				str[newlen--] = '%';
			}
			
		}
	}	
}


int main(){

	fstream fin("./input/input04");
	
	while(fin.getline(str, sizeof(str))){
		
		int length = strlen(str)+1;
		cout << "string: " << str << endl;
		replaceSpace1(str, length);
		cout << "After replace space : " << str << endl;

	}
	
	return 0;
}
