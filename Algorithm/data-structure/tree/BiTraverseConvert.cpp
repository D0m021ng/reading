#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct BiTree{
    char elem;
    BiTree *lchild, *rchild;
    BiTree(char _elem, BiTree *l = nullptr, BiTree *r = nullptr)
        : elem(_elem), lchild(l), rchild(r) {}
};

/**
 *   二叉树根据前序遍历和中序遍历，求后序遍历。递归方式实现
 *   思路：由前序遍历确定根节点，然后根据中序遍历划分左、右子树的前序和中序遍历；
 *         对左右子树递归下去
 *   @param  preorder 二叉树的前序遍历
 *   @param  inorder  二叉树的中序遍历
 *   @param  **BT     指向二叉树根指针的指针
 *   @param  &post    记录二叉树的后序遍历
 *   @return         无
 */
void BiTreeFromPreInOrderToPost(const string preorder, const string inorder, BiTree **BT, string &post){
    // 递归退出条件
    if(preorder.size() == 0 || inorder.size() == 0){
        return ;
    }

    // 获取根节点，并创建节点
    char root = preorder[0];
    *BT = new BiTree(root);
   
    // 根据中序遍历和根节点，划分左、右子树的前序和中序遍历
    string lpre(""), rpre(""), lin(""), rin("");
    int i;
    // 获取左子树的前序遍历lpre和中序遍历lin
    for(i = 0; i < inorder.size(); ++i){
        if(inorder[i] != root){
            lin  += inorder[i];
            lpre += preorder[i+1];
        }else{
            break;
        }
    }
    // 获取右子树的前序遍历rpre和中序遍历rin
    for(i = i+1; i < inorder.size(); ++i){
        rin  += inorder[i];
        rpre += preorder[i];
    }

    // 递归遍历左子树
    BiTreeFromPreInOrderToPost(lpre, lin, &(*BT)->lchild, post);
    // 递归遍历右子树
    BiTreeFromPreInOrderToPost(rpre, rin, &(*BT)->rchild, post);
    // 访问根节点
    post += root;
}

/**
 *   二叉树根据中序遍历和后序遍历，求前序遍历。递归方式实现
 *   思路：由后序遍历确定根节点，然后根据中序遍历划分左、右子树的中序遍历和后序遍历；
 *         对左右子树递归下去
 *   @param  inorder 二叉树的中序遍历
 *   @param  postorder  二叉树的后序遍历
 *   @param  **BT     指向二叉树根指针的指针
 *   @param  &pre    记录二叉树的前序遍历
 *   @return         无
 */
void BiTreeFromPostInOrderToPre(const string inorder, const string postorder, BiTree **BT, string &pre){
    // 递归退出条件    
    if(inorder.size() == 0 || postorder.size() == 0){
        return ;
    }
     // 获取根节点，并创建节点
    char root = postorder[postorder.size()-1];
    *BT = new BiTree(root);

    // 根据中序遍历和根节点，划分左、右子树的中序和后序遍历
    string lin(""), lpost(""), rin(""), rpost("");
    int i;
    // 获取左子树的中序遍历lin和后序遍历lpost
    for(i = 0; i < inorder.size(); ++i){
        if(inorder[i] != root){
            lin += inorder[i];
            lpost += postorder[i];
        }else{
            break;
        }
    }
    // 获取右子树的中序遍历rin和后序遍历rpost
    for(i = i+1; i < inorder.size(); ++i){
        rin += inorder[i];
        rpost += postorder[i-1];
    }

    // 访问根节点
    pre += root;
    // 递归遍历左子树
    BiTreeFromPostInOrderToPre(lin, lpost, &(*BT)->lchild, pre);
    // 递归遍历右子树
    BiTreeFromPostInOrderToPre(rin, rpost, &(*BT)->rchild, pre);
}

void BiTreePostTraverse(BiTree *T){
    if(T){
        BiTreePostTraverse(T->lchild);
        BiTreePostTraverse(T->rchild);
        cout << T->elem << " ";
    }
}

void BiTreePreTraverse(BiTree *T){
    if(T){
        cout << T->elem << " ";
        BiTreePreTraverse(T->lchild);
        BiTreePreTraverse(T->rchild);     
    }
}

int main(int argc, char *argv[]){
    
    string pre, in, post;
    ifstream fin("input");
    while(fin >> pre >> in >> post){

        cout <<"preorder: " << pre << ", inorder: " << in << ", postorder: " << post << endl;
        BiTree *T, *T1;
        string ans, anspre;
        BiTreeFromPreInOrderToPost(pre, in, &T, ans);
        cout << "Post Traverse : " << ans << endl;
        // BiTreePostTraverse(T);
        // cout << endl;

        BiTreeFromPostInOrderToPre(in, post, &T1, anspre);
        cout << "Pre Traverse : " << anspre << endl ;
        // BiTreePreTraverse(T1);
        // cout << endl;
    }

    return 0;
}
