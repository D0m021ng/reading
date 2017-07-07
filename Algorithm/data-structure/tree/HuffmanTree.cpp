#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
using namespace std;

struct HTNode{
	int weight;                   // 节点的权值
	char ch;                      // 节点表示的字符
	string encode;                // 节点的哈夫曼编码
	HTNode *lchild, *rchild;      // 节点的左右子树指针
	HTNode(char c, int x, HTNode *l = NULL, HTNode *r = NULL, string pt = "") 
		: ch(c), weight(x), lchild(l), rchild(r), encode(pt) {}

    // 重载<运算符，优先队列中会用到
	bool operator<(const HTNode &node) const{ 
		return weight > node.weight;
	}
};

/** 构建哈夫曼树 HuffmanTree
 *  思路：贪心算法，首先，创建n个根节点带权的子树； 每次从子树中选择根节点
 *        权值最小的两个进行合并；重复第二步，直到只剩下一颗树。
 *  实现：采用优先队列的数据结构，先将n个叶子节点构成的子树进优先队列；每次
 *        从优先队列中取出权值最小的两个子树，合并后加入到优先队列；重复
 *        以上第二步，直到优先队列中只剩下一个节点。
 *  @param  Huff    用以返回哈夫曼树的根节点
 *  @param  weight  表示每个字符出现的次数 
 *  @return ret     返回哈夫曼树的最短带权路经的长度
 */
int HuffmanTree(priority_queue<HTNode> &Huff, map<char, int> weight){

	// 初始化优先队列
	for(auto &t : weight){
		HTNode htnode(t.first, t.second);
		Huff.push(htnode);
	}

    // 记录最短带权路经长度
	int ret = 0;
	// 当优先队列长度大于1时 
	while(Huff.size() != 1){
        // 取出权值最小的两个节点，并创建子树
		HTNode *left = new HTNode(Huff.top());
		Huff.pop();
		HTNode *right = new HTNode(Huff.top());
		Huff.pop();

        // 合并两个子树，节点进入队列
		HTNode parent('+', left->weight + right->weight, left, right);
		Huff.push(parent);
        // 最短带权路经长度增加
		ret += left->weight + right->weight;
	}
	return ret;
}

string HuffmanEncoding(HTNode *HT, string src){
	map<char, string> Huffmancode;
	if(HT){
		queue<HTNode *> Q;
		Q.push(HT);

		while(!Q.empty()){
			HTNode *p = Q.front();
			Q.pop();

			if(!p->lchild && !p->rchild){
				Huffmancode[p->ch] = p->encode;
				cout << p->ch << " Huffmancode is :" << p->encode << endl;
			}

			if(p->lchild){			
				(p->lchild)->encode = p->encode + '0';
				Q.push(p->lchild);
			}

			if(p->rchild){
				(p->rchild)->encode = p->encode + '1';
				Q.push(p->rchild);
			}
		}
	}

	string res = "";
	for(auto &t : src)
		res += Huffmancode[t];

	return res;
}

string HuffmanDecoding(HTNode *HT, string Enstr){
	string Destr = "";
	HTNode *p = HT;

	for(auto &c : Enstr){

		if(c == '0' && p->lchild)
			p = p->lchild;
		if(c == '1' && p->rchild)
			p = p->rchild;

		if(!p->lchild && !p->rchild){
			Destr += p->ch;
			p = HT;
		}
	}

	return Destr;
}

int main(int argc, char *argv[]){

	string str;

	while(cin >> str){
		map<char, int> chw;
		for(auto t : str){
			chw[t]++;
		}

		priority_queue<HTNode> HuffTree;
		int ans = HuffmanTree(HuffTree, chw);
		cout << ans << endl;

		HTNode HT = HuffTree.top();
		
		string Enstr = HuffmanEncoding(&HT, str);
		cout << "HuffmanEncoding: " << Enstr << endl;

		cout << "HuffmanDecoding: " << HuffmanDecoding(&HT, Enstr) << endl;

	}
	return 0;
		
}
