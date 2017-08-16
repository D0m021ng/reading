#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

bool IsPopOrder(vector<int> pushV,vector<int> popV) {
    if(pushV.size() != popV.size() || pushV.size() < 1)
        return false;
    
    stack<int> tmp;
    int i = 0, j = 0;
    while(i < pushV.size()){
        if(pushV[i] != popV[j]){
            tmp.push(pushV[i]);
            ++i;
        }else{
        	++i;
        	++j;
            while(!tmp.empty() && tmp.top() == popV[j]){
                tmp.pop();
                ++j;
            }
        }
    }

    if(tmp.empty())
        return true;
    else
        return false;
} 

int main(){
	int n;
	fstream fin("./input/input21");

	while(fin >> n){
		vector<int> pushV(n), popV(n);
		for(int i = 0; i < n; ++i)
			fin >> pushV[i];
		for(int i = 0; i < n; ++i)
			fin >> popV[i];
/*
		for(auto t : pushV)
			cout << t << " ";
		cout << endl;


		for(auto t : popV)
			cout << t << " ";
		cout << endl;
*/
		if(IsPopOrder(pushV, popV))
			cout << "true" << endl;
		else
			cout << "false" << endl;

		
	}
	return 0;
}
