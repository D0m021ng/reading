#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct BiSTNode{
    int data;
    BiSTNode *lchild, *rchild;
    BiSTNode(int _data, BiSTNode *l = NULL, BiSTNode *r = NULL)
        : data(_data), lchild(l), rchild(r) {}
};

/******************************************************************
 *  二叉查找树的查找操作，C++实现
 *  思路： 若当前的二叉查找树为空，则返回查找失败；
 *        若当前的二叉查找树不空，且查找元素与根节点元素相同，则返回查找成功；
 *        若查找的元素值小于根节点值，则将到左子树中继续查找；
 *        若查找的元素值大于根节点值，则将到右子树中继续查找。
 *  @param  BT   二叉查找树
 *  @param  key  需要查找的元素
 *  @return      查找成功返回true，否则返回false
 *******************************************************************
 */
bool SearchBST(BiSTNode *BT, int key){
    if(BT){
        // 当二叉查找树不空时，
        if(key == BT->data){
            // 查找成功
            return true;
        }else if(key < BT->data){
            // 查找元素小于根节点值，在左子树中继续查找
            return SearchBST(BT->lchild, key);
        }else{
            // 查找元素大于根节点值，在右子树中继续查找
            return SearchBST(BT->rchild, key);
        }
    }else{
        // 查找失败
        return false;
    }
}

/******************************************************************
 *  二叉查找树的插入操作，C++递归实现
 *  思路： 若当前的二叉查找树为空，则插入的元素为根节点；
 *         若插入的元素值小于根节点值，则将元素插入到左子树；
 *         若插入的元素值大于根节点值，则将元素插入到右子树。
 *  @param  BT   需要插入元素的二叉查找树
 *  @param  key  需要插入的元素
 *  @return      无返回值
 *******************************************************************
 */
void InsertBST(BiSTNode **BT, int key){

    if(*BT == NULL){
        // 当二叉查找树为空时，创建节点并插入。
        BiSTNode *p = new BiSTNode(key);
        *BT = p;

    }else if(key < (*BT)->data){
        // 当插入的元素值小于根节点值时，将元素插入到左子树
        InsertBST(&(*BT)->lchild, key);
        
    }else if(key > (*BT)->data){
        // 当插入的元素值大于根节点值时，将元素插入到右子树
        InsertBST(&(*BT)->rchild, key);
    }
}

/******************************************************************
 *  二叉查找树的删除操作，C++非递归实现
 *  思路： 先找到需要删除元素的位置，得到删除节点和其父节点；
 *         如果删除节点是叶子节点，则直接置空；
 *         如果删除节点只有左子树或右子树，将子树设为父节点
 *             的左子树或右子树；
 *         如果删除节点左子树和右子树均不空，先找到删除节点
 *             的前驱节点，用前驱节点值代替删除节点，删除前
 *             驱节点。
 *
 *  @param  BT   需要删除元素的二叉查找树
 *  @param  key  需要删除的元素
 *  @return      返回是否删除元素成功
 *******************************************************************
 */
bool DeleteBST(BiSTNode **BT, int key){
 
    // 寻找需要删除的元素位置，返回该元素节点以及父节点
    BiSTNode *p = *BT, *parent;
    while(p){
        if(p->data == key){
            break;
        }else if(p->data > key){
            parent = p;
            p = p->lchild;
        }else{
            parent = p;
            p = p->rchild;
        }
    }

    // 若元素不存在，则返回删除失败
    if(!p){
        return false;
    }

    if(!p->lchild && !p->rchild){
        // 如果需要删除的节点是叶子节点，直接置空
        // 父节点对应的左孩子或右孩子
        if(p == *BT){
            *BT = NULL;
        }else if(parent->lchild == p){
            parent->lchild = NULL;
        }else{
            parent->rchild = NULL;
        }

        delete p;
    }else if(!p->lchild){
        // 如果需要删除的节点只有右子树，将该节点
        // 的右子树设置为父节点的左孩子或右孩子
        if(p == *BT){
            *BT = p->rchild;
        }else if(parent->lchild == p){
            parent->lchild = p->rchild;
        }else{
            parent->rchild = p->rchild;
        } 
           
        delete p;
    }else if(!p->rchild){
        // 如果需要删除的节点只有左子树，将该节点
        // 的左子树设置为父节点的左孩子或右孩子
        if(p == *BT){
            *BT = p->lchild;
        }else if(parent->lchild == p){
            parent->lchild = p->lchild;
        }else {
            parent->rchild = p->lchild;
        }

        delete p;
    }else{
        // 需要删除的节点p左右子树均不空
        // 从p的左子树根节点开始，寻找节点p的前驱节点s，
        // 节点p的前驱节点s没有右子树
        BiSTNode *s = p->lchild, *t = p;
        while(s->rchild){
            t = s;
            s = s->rchild;
        }
        // 将前驱节点s的值赋给节点p
        p->data = s->data;

        // 删除前驱节点s
        if(t == p){
            // 前驱节点s为节点p的左子节点
            p->lchild = s->lchild;
        }else{
            // 普通前驱节点删除
            t->rchild = s->lchild;
        }

        delete s;
    }
    return true;
}

bool DeleteBST2(BiSTNode **BT, int key){
 
    // 寻找需要删除的元素位置，返回该元素节点以及父节点
    BiSTNode *p = *BT, *parent;
    while(p){
        if(p->data == key){
            break;
        }else if(p->data > key){
            parent = p;
            p = p->lchild;
        }else{
            parent = p;
            p = p->rchild;
        }
    }

    // 若元素不存在，则返回删除失败
    if(!p){
        return false;
    }

    if(!p->lchild && !p->rchild){
        // 如果需要删除的节点是叶子节点，直接置空
        // 父节点对应的左孩子或右孩子
        if(p == *BT){
            *BT = NULL;
        }else if(parent->lchild == p){
            parent->lchild = NULL;
        }else{
            parent->rchild = NULL;
        }

        delete p;
    }else if(!p->lchild){
        // 如果需要删除的节点只有右子树，将该节点
        // 的右子树设置为父节点的左孩子或右孩子
        if(p == *BT){
            *BT = p->rchild;
        }else if(parent->lchild == p){
            parent->lchild = p->rchild;
        }else{
            parent->rchild = p->rchild;
        } 
           
        delete p;
    }else if(!p->rchild){
        // 如果需要删除的节点只有左子树，将该节点
        // 的左子树设置为父节点的左孩子或右孩子
        if(p == *BT){
            *BT = p->lchild;
        }else if(parent->lchild == p){
            parent->lchild = p->lchild;
        }else {
            parent->rchild = p->lchild;
        }

        delete p;
    }else{
        // 需要删除的节点p左右子树均不空
        // 从p的右子树根节点开始，寻找节点p的后继节点s，
        // 节点p的后继节点s没有左子树
        BiSTNode *s = p->rchild, *t = p;
        while(s->lchild){
            t = s;
            s = s->lchild;
        }
        // 将后继节点s的值赋给节点p
        p->data = s->data;

        // 删除后继节点s
        if(t == p){
            // 后继节点s为节点p的右子节点
            p->rchild = s->rchild;
        }else{
            // 普通后继节点删除
            t->lchild = s->rchild;
        }

        delete s;
    }
    return true;
}

// 二叉查找树的中序遍历 
void BSTInorderTraverse(BiSTNode *BT){
    if(BT){
        BSTInorderTraverse(BT->lchild);
        cout << BT->data << " ";
        BSTInorderTraverse(BT->rchild);
    }
}

// 二叉查找树的前序遍历
void BSTPreorderTraverse(BiSTNode *BT){
    if(BT){
        cout << BT->data << " ";
        BSTPreorderTraverse(BT->lchild);
        BSTPreorderTraverse(BT->rchild);
    }
}

int main(int argc, char *argv[]){

    int n, val;

    ifstream fin("input_bst");
    while(fin >> n){
        BiSTNode *BST = NULL;        
        for(int i = 0; i < n; ++i){
            fin >> val; 
            InsertBST(&BST, val);   
        }

        BSTInorderTraverse(BST);
        cout << endl;
        BSTPreorderTraverse(BST);
        cout << endl << "please input value to be deleted: ";

        while(cin >> val){
            if(SearchBST(BST, val)){
                cout << "val in BST!" << endl;
                DeleteBST2(&BST, val);
            }
                  
            BSTInorderTraverse(BST);
            cout << endl;
            BSTPreorderTraverse(BST);
            cout << endl;
        }
    }

    return 0;
}


// bool SearchBST1(BiSTNode *BT, int key, BiSTNode* pre, BiSTNode* &p){
//     if(!BT){
//         p = pre;
//         return false;
//     }
    
//     if(key == BT->data){
//         p = BT;
//         return true;
//     }else if(key < BT->data){
//         return SearchBST1(BT->lchild, key, BT, p);
//     }else{
//         return SearchBST1(BT->rchild, key, BT, p);
//     }
// }

// void InsertBST1(BiSTNode **BT, int key){
    
//     BiSTNode *p;
//     if(!SearchBST1(*BT, key, NULL, p)){
//         BiSTNode *bistnode = new BiSTNode(key);

//         if(!p){
//             *BT = bistnode;
//         }else if(p->data > key){
//             p->lchild = bistnode;
//         }else{
//             p->rchild = bistnode;
//         }
//     }
// }
