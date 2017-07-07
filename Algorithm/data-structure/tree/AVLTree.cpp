#include <iostream>
#include <fstream>
using namespace std;

struct AVLTNode{
    int data;   // 数据域 
    int hgt;    // 树高度
    int freq;   // 数据的频度
    AVLTNode *lchild, *rchild;
    AVLTNode(int _data, int _hgt, int _freq = 1, AVLTNode *l = NULL, AVLTNode *r = NULL)
        : data(_data), hgt(_hgt), freq(_freq), lchild(l), rchild(r) {}                
};

// 计算树的高度
int height(AVLTNode *AT){
    if(AT)
        return AT->hgt;
    else
        return 0;
}

// 从两个数中选择较大者
int Max(int cmpa, int cmpb){
    return cmpa > cmpb? cmpa : cmpb;
}

/**********************************************************************************
 *  左左情况下的旋转： 以AT根节点为轴，顺时针右旋
 *  @param   AT 需要旋转调整的平衡二叉树
 *  @return  无返回值
 **********************************************************************************
 */  
void LL_Rotate(AVLTNode* &AT){
    AVLTNode *p = AT->lchild;
    AT->lchild = p->rchild;
    p->rchild = AT;
    
    AT->hgt = Max(height(AT->lchild), height(AT->rchild)) + 1; 
    p->hgt = Max(height(p->lchild), AT->hgt) + 1;
    AT = p;
}

/**********************************************************************************
 * 右右情况下的旋转： 以AT根节点为轴，逆时针左旋
 * @param   AT 需要旋转调整的平衡二叉树
 * @return  无返回值
 **********************************************************************************
 */
void RR_Rotate(AVLTNode* &AT){
    AVLTNode *p = AT->rchild;
    AT->rchild = p->lchild;
    p->lchild = AT;

    AT->hgt = Max(height(AT->lchild), height(AT->rchild)) + 1;
    p->hgt = Max(AT->hgt, height(p->rchild)) + 1;
    AT = p;
}

/***********************************************************************************
 * 左右情况下的旋转： 
 * 先以AT的左子树根节点为轴，右右情况下逆时针左旋；
 * 再以AT的根节点为轴，左左情况下顺时针右旋。
 * @param   AT 需要旋转调整的平衡二叉树
 * @return  无返回值
 ***********************************************************************************
 */
void LR_Rotate(AVLTNode* &AT){
    RR_Rotate(AT->lchild);
    LL_Rotate(AT);
}

/***********************************************************************************
 * 右左情况下的旋转：
 * 先以AT的右子树根节点为轴，左左情况下顺时针右旋；
 * 再以AT的根节点为轴，右右情况下逆时针左旋。
 * @param   AT 需要旋转调整的平衡二叉树
 * @return  无返回值
 ***********************************************************************************
 */
void RL_Rotate(AVLTNode* &AT){
    LL_Rotate(AT->rchild);
    RR_Rotate(AT);
}

/***********************************************************************************
 *  平衡二叉树的插入操作，C++递归实现
 *  思路： 采用递归的思想，当子树为空时，创建节点并插入；
 *         当插入的值小于根节点值，在左子树中插入，如果不平衡，则旋转左子树；
 *         当插入的值大于根节点值，在右子树中插入，如果不平衡，则旋转右子树；
 *         当插入的值等于根节点值，则增加值出现的频度。
 *  @param    AT  需要插入值的平衡二叉树 
 *  @param    x   插入值
 *  @return   无返回值
************************************************************************************
 */
void InsertAVLTree(AVLTNode* &AT, int x){
    // 当平衡二叉树为空时，创建节点并插入
    if(!AT){
        AVLTNode *p = new AVLTNode(x, 1);
        AT = p;
        return;
    } 

    // 平衡因子
    int bf;
    if(x < AT->data){
        // 当插入的值小于根节点的值，在左子树中插入
        InsertAVLTree(AT->lchild, x);
        bf = height(AT->lchild) - height(AT->rchild);
        // 左子树中插入值之后，导致不平衡，旋转左子树
        if(bf == 2){
            if(x < AT->lchild->data){
                // 插入点在左子树根节点的左子树上，进行左左情况旋转 
                LL_Rotate(AT);
            }else{
                // 插入点在左子树根节点的右子树上，进行左右情况旋转
                LR_Rotate(AT);
            }
        }
    }else if(x > AT->data){
        // 当插入的值大于根节点的值，在右子树中插入
        InsertAVLTree(AT->rchild, x);
        bf = height(AT->lchild) - height(AT->rchild);
        // 右子树中插入值之后，导致不平衡，旋转右子树
        if(bf == -2){
            if(x > AT->rchild->data){
                // 插入点在右子树根节点的右子树上，进行右右情况旋转
                RR_Rotate(AT);
            }else{
                // 插入点再右子树根节点的左子树上，进行右左情况旋转
                RL_Rotate(AT);
            }
        }
    }else{
        // 当插入的值等于根节点的值，增加值出现的频度
        AT->freq++;
    }

    // 调整树的高度
    AT->hgt = Max(height(AT->lchild), height(AT->rchild));   
}

/***********************************************************************************
 *  平衡二叉树的删除操作，C++递归实现，比较复杂
 *  思路： 采用递归的思想，当子树为空时，直接返回；
 *         当删除的值小于根节点值，在左子树中删除，删除后如果不平衡，则旋转右子树；
 *         当删除的值大于根节点值，在右子树中删除，删除后如果不平衡，则旋转左子树；
 *         当删除的值等于根节点值，分两种情况：
 *              1）删除节点左右子树均不空，找到删除节点的后继节点，以后继节点值代
 *                 替删除节点，然后删除后继节点。
 *              2）删除节点左右子树至少有一个为空，以删除节点的左子树或右子树根顶
 *                 上，删除该节点
 *         最后调整一下删除后，平衡二叉树的高度
 *  @param    AT  需要删除值的平衡二叉树 
 *  @param    x   删除值
 *  @return   无返回值
 ************************************************************************************
 */
void DeleteAVLTree(AVLTNode* &AT, int x){
    // 当平衡二叉树为空时，直接返回
    if(!AT){
        return ;
    }

    int bf;
    if(x < AT->data){
        // 当删除值小于根节点的值，在左子树中删除
        DeleteAVLTree(AT->lchild, x);
        bf = height(AT->lchild) - height(AT->rchild);
        // 左子树删除值之后，导致不平衡，旋转右子树
        if(bf == -2){
            if(!AT->rchild->lchild && height(AT->rchild->lchild) > height(AT->rchild->rchild)){
                // 当右子树根节点的左子树存在且高度比右子树的右子树高
                // 进行右左情况下旋转
                RL_Rotate(AT);
            }else{
                // 否则，进行右右情况旋转
                RR_Rotate(AT);
            }
        }
    }else if(x > AT->data){
        // 当删除值大于根节点的值，在右子树中删除
        DeleteAVLTree(AT->rchild, x);
        bf = height(AT->lchild) - height(AT->rchild);
        // 右子树删除值之后，导致不平衡，旋转左子树
        if(bf == 2){
            if(!AT->lchild->rchild && height(AT->lchild->lchild) < height(AT->lchild->rchild)){
                // 当左子树根节点的右子树存在且高度比左子树的左子树高
                // 进行左右情况下旋转
                LR_Rotate(AT);
            }else{
                // 否则，进行左左情况旋转
                LL_Rotate(AT);
            }
        }
    }else{
        // 当删除值等于根节点的值，删除该节点，分两种情况
        if(AT->lchild && AT->rchild){
            // 当删除节点的左右子树均不空时，
            // 在右子树中，找到删除节点的中序遍历后继节点
            AVLTNode *p = AT->rchild;
            while(p->lchild)
                p = p->lchild;
            
            // 用后继节点的值代替删除节点 
            AT->data = p->data;
            AT->freq = p->freq;

            // 在右子树中删除该后继节点，注意后继节点无左子树
            DeleteAVLTree(AT->rchild, p->data);
            bf = height(AT->lchild) - height(AT->rchild);
            // 在右子树中删除后继节点，导致不平衡，旋转左子树
            if(bf == 2){
                if(!AT->lchild->rchild && height(AT->lchild->lchild) < height(AT->lchild->rchild)){
                    // 当左子树根节点的右子树存在且高度比左子树的左子树高
                    // 进行左右情况下旋转
                    LR_Rotate(AT);
                }else{
                    // 否则，进行左左情况旋转
                    LL_Rotate(AT);
                }
            }
        }else{
            // 当删除节点的左右子树至少有一个为空时
            AVLTNode *p = AT;
            if(!AT->lchild){
                // 删除节点的右子树不空，右子树代替删除节点
                AT = AT->rchild;
            }else if(!AT->rchild){
                // 删除节点的左子树不空，左子树代替删除节点
                AT = AT->lchild;
            }
            
            // 删除该节点
            delete p;
            p = NULL;
        }

    }

    // 最后，调整删除值之后，平衡二叉树的高度
    if(!AT){
        return;
    }else{
        AT->hgt = Max(height(AT->lchild), height(AT->rchild)) + 1;
        return;
    }
}


/************************************************************************************************
 *   平衡二叉树的查找操作，非递归实现
 *   @param   AT  平衡二叉树
 *   @param   x   查找的值
 *   @return  查找成功，返回true；否则，返回false
 ************************************************************************************************   
 */
bool SearchAVLTree(AVLTNode *AT, int x){
    AVLTNode *p = AT;

    while(p){
        if(x == p->data){
            return true;
        }else if(x < p->data){
            p = p->lchild;
        }else if(x > p->data){
            p = p->rchild;
        }
    }

    return false;
}

// 二叉查找树的中序遍历 
void AVLTInorderTraverse(AVLTNode *AT){
    if(AT){
        AVLTInorderTraverse(AT->lchild);
        cout << AT->data << " ";
        AVLTInorderTraverse(AT->rchild);
    }
}

// 二叉查找树的前序遍历
void AVLTPreorderTraverse(AVLTNode *AT){
    if(AT){
        cout << AT->data << " ";
        AVLTPreorderTraverse(AT->lchild);
        AVLTPreorderTraverse(AT->rchild);
    }
}


int main(int argc, char* argv[]){

    int n, val;

    ifstream fin("input_bst");
    while(fin >> n){

        AVLTNode *AVL = NULL;
        for(int i = 0; i < n; ++i){
            fin >> val;
            InsertAVLTree(AVL, val);
        }
        cout << "PreOrder: ";
        AVLTPreorderTraverse(AVL);
        cout << "\nInOrder: ";
        AVLTInorderTraverse(AVL);
        cout << endl;

        while(cin >> val){
            if(val == -1)
                break;
            if(SearchAVLTree(AVL, val))
                cout << "Value in VALTree!" << endl;
            DeleteAVLTree(AVL, val);
            cout << "PreOrder: ";
            AVLTPreorderTraverse(AVL);
            cout << "\nInOrder: ";
            AVLTInorderTraverse(AVL);
            cout << endl;
        }
    }
    

    return 0;
}


// void InsertAVLTree1(AVLTNode** AT, int x){
//     if(!(*AT)){
//         AVLTNode *p = new AVLTNode(x, 1);
//         *AT = p;
//         return;
//     } 

//     int bf;
//     if(x < (*AT)->data){
//         InsertAVLTree1(&(*AT)->lchild, x);
//         bf = height((*AT)->lchild) - height((*AT)->rchild);
//         if(bf == 2){
//             if(x < (*AT)->lchild->data)
//                 LL_Rotate(*AT);
//             else
//                 LR_Rotate(*AT);
//         }
//     }else if(x > (*AT)->data){
//         InsertAVLTree1(&(*AT)->rchild, x);
//         bf = height((*AT)->rchild) - height((*AT)->lchild);
//         if(bf == 2){
//             if(x > (*AT)->rchild->data)
//                 RR_Rotate(*AT);
//             else
//                 RL_Rotate(*AT);
//         }
//     }else{
//         (*AT)->freq++;
//     }

//     (*AT)->hgt = Max(height((*AT)->lchild), height((*AT)->rchild));   
// }
