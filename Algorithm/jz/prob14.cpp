#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct ListNode{
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
}; 

ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
		
    if(pListHead != nullptr && k > 0){
     	ListNode *p1 = pListHead, *p2 = pListHead;          
        
        int i;
        for(i = 0; i < k && p2; ++i)
            p2 = p2->next;
        
        if(i < k){
           return nullptr; 
        }else{
         	while(p2){
                p2 = p2->next;
                p1 = p1->next;
            }   
            return p1;
        }
    }else{
        return nullptr;
    }
}

ListNode* ReverseList(ListNode* pHead) {
	ListNode *pre = nullptr, *post = pHead;
			
	while(post){
		ListNode *p = post->next;
		post->next = pre;
		pre = post;
		post = p;	
	}
	
	return pre;
}

ListNode* Merge(ListNode* pHead1, ListNode* pHead2){
 	ListNode *res = new ListNode(0), *p;

 	p = res;
 	while(pHead1 && pHead2){
 		if(pHead1->val <= pHead2->val){
 			p->next = pHead1;
 			p = pHead1;
 			pHead1 = pHead1->next;
 			p->next = nullptr;
 		}else{
 			p->next = pHead2;
 			p = pHead2;
 			pHead2 = pHead2->next;
 			p->next = nullptr;
 		}
 	}

 	if(pHead1){
 		p->next = pHead1;
 	}

 	if(pHead2){
 		p->next = pHead2;
 	}
 	return res->next;
}

ListNode* Merge1(ListNode* pHead1, ListNode* pHead2){
 	ListNode *res = new ListNode(0), *p1 = pHead1, *p2 = pHead2, *p;

 	p = res;
 	while(p1 && p2){
 		if(p1->val <= p2->val){
 			p->next = p1;
 			p = p1;
 			p1 = p1->next;
 			p->next = nullptr;
 		}else{
 			p->next = p2;
 			p = p2;
 			p2 = p2->next;
 			p->next = nullptr;
 		}
 	}

 	if(p1){
 		p->next = p1;
 	}

 	if(p2){
 		p->next = p2;
 	}
 	return res->next;
}


void createlist(istream &fin, ListNode** list, int m){
		ListNode *p1;
		int x;

		fin >> x;
		*list = new ListNode(x);
		p1 = *list;
		for(int i = 1; i < m; ++i){
			fin >> x;
			ListNode *p = new ListNode(x);
			p1->next = p;
			p1 = p;
		}
}


int main(){
	int n, k;
	fstream fin("./input/input14");

	while(fin >> n >> k){
		ListNode *lista, *listb, *p1;
		
		createlist(fin, &lista, n);
		createlist(fin, &listb, k);

		p1 = lista;
		while(p1){
			cout << p1->val << " ";
			p1 = p1->next;
		}
		cout << endl;
		
		p1 = listb;
		while(p1){
			cout << p1->val << " ";
			p1 = p1->next;
		}
		cout << endl;

/*		p1 = FindKthToTail(lista, k);
		if(p1){
			cout << (*p1).val << endl;
		}else{
			cout << "ERROR" << endl;
		}
*/
/*		p1 = ReverseList(lista);
		while(p1){
			cout << p1->val << " ";
			p1 = p1->next;
		}
		cout << endl;	*/

		p1 = Merge(lista, listb);
		while(p1){
			cout << p1->val << " ";
			p1 = p1->next;
		}
		cout << endl;



	}
	return 0;
}
