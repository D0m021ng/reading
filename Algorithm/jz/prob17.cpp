#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
 
struct TreeNode{
	int val;
	struct TreeNode *left, *right;
	TreeNode(int x) : 
		val(x), left(nullptr), right(nullptr) {}
};

vector<int> PrintFromTopToBottom(TreeNode* root){
    vector<int> res;
	
    if(root){
    	queue<TreeNode* > Q;
        Q.push(root);
        
        while(!Q.empty()){
            TreeNode* p = Q.front();
            Q.pop();
            
            res.push_back(p->val);
            if(p->left)
                Q.push(p->left);
            if(p->right)
                Q.push(p->right);
        }
    }
    
	return res;
}

void createTree(istream &fin, TreeNode **rt){

	char x;
	fin >> x;
	if(x != '#')
	if(*rt){
		*rt = new TreeNode(x);
	}
}

int main(){
	int n;
	fstream fin("./input/input17");

	while(fin >> n){
		
	}
	return 0;
}
