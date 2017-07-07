#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
} *BiTree;

// 前序创建二叉树
void CreateBiTree(BiTree *B, ifstream &fin){  
    char val;
    
    fin >> val;
    if(val == '.')
        *B = nullptr;
    else{
        *B = new BiTNode;
        
        if(!B){
            cout << "malloc ERROR!";
        }
        (*B)->data = val;
        //前序创建
        CreateBiTree(&(*B)->lchild, fin);
        CreateBiTree(&(*B)->rchild, fin);
    } 
}

// 前序遍历二叉树，递归实现
void PreOrderTraverse(BiTree T){
    if(T){
        cout << T->data << " ";
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);

    }
}

// 前序遍历二叉树，利用栈非递归实现
void PreOrderTraverse_NR(BiTree T){
    if(T){
        stack<BiTree> S;
        S.push(T);

        while(!S.empty()){
            BiTree p = S.top();
            S.pop();

            cout << p->data << " ";
            if(p->rchild){
                S.push(p->rchild);
            }
            if(p->lchild){
                S.push(p->lchild);
            }
        }
    }
}

// 中序遍历二叉树，递归实现
void InOrderTraverse(BiTree T){
    if(T){
        InOrderTraverse(T->lchild);
        cout << T->data << " ";
        InOrderTraverse(T->rchild);
    }
}

// 中序遍历二叉树，利用栈非递归实现1
void InOrderTraverse_NR(BiTree T){
    stack<BiTree> S;
    S.push(T);

    while(!S.empty()){
        while(S.top()){
            S.push((S.top())->lchild);
        }

        S.pop();
        if(!S.empty()){
            BiTree p = S.top();
            cout << p->data << " ";
            S.pop();
            S.push(p->rchild);
        }
    }
}

// 中序遍历二叉树，利用栈非递归实现2
void InOrderTraverse_NR2(BiTree T){
    stack<BiTree> S;
    BiTree p = T;

    while(p || !S.empty()){       
        if(p){
            S.push(p);
            p = p->lchild;
        }else{
            cout << S.top()->data << " ";
            p = S.top()->rchild;
            S.pop();
        }
    }
}

// 后序遍历二叉树，递归实现
void PostOrderTraverse(BiTree T){
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data << " ";
    }
}

// 后序遍历二叉树，非递归实现
void PostOrderTraverse_NR(BiTree T){
    if(T){
        stack<BiTree> S, Res;
        S.push(T);

        while(!S.empty()){
            BiTree p = S.top();
            S.pop();
            //
            Res.push(p);
            //
            if(p->lchild){
                S.push(p->lchild);
            }
            if(p->rchild){
                S.push(p->rchild);
            }
        }

        while(!Res.empty()){
            cout << Res.top()->data << " ";
            Res.pop();
        }

    }
}

// 层序遍历二叉树，BFS
void LevelOrderTraverse(BiTree T){
    if(T){
        queue<BiTree> Q;
        Q.push(T);

        while(!Q.empty()){
            BiTree p = Q.front();
            Q.pop();
            
            cout << p->data << " ";
            if(p->lchild){
                // cout << p->lchild->data << " ";
                Q.push(p->lchild);
            }

            if(p->rchild){
                // cout << p->rchild->data << " ";
                Q.push(p->rchild);
            }
        }

    }
}

int main(int argc, char *argv[]){
    
    BiTree B = nullptr;
    cout << "请使用前序遍历的方式输入字符串，用.代替空值\n";
    ifstream fin("input_bintree");
    CreateBiTree(&B, fin);
    
    cout << "建树成功！\n前序遍历二叉树（递归 ）： ";
    PreOrderTraverse(B);
    cout << "\n前序遍历二叉树（非递归）: ";
    PreOrderTraverse_NR(B);
    
    cout << "\n\n中序遍历二叉树（递归 ）： ";
    InOrderTraverse(B);
    cout << "\n中序遍历二叉树（非递归）： ";
    InOrderTraverse_NR2(B);

    cout << "\n\n后序遍历二叉树（递归 ）： ";
    PostOrderTraverse(B);
    cout << "\n后序遍历二叉树（非递归）： ";
    PostOrderTraverse_NR(B);    
    
    cout << "\n\n层序遍历二叉树： ";
    LevelOrderTraverse(B);
    cout << endl;
    
    return 0;
}
