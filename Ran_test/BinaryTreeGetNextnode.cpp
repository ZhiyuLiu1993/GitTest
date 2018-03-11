#include <iostream>

//寻找二叉树下一个节,通过画图抽象出来，有右儿子，则是其右儿子最左边的点，没有右儿子，则是其当前节点为左儿子时的父节点

typedef struct BINARY_TREE_NODE_{
    int value;
    BINARY_TREE_NODE_ *left;
    BINARY_TREE_NODE_ *right;
    BINARY_TREE_NODE_ *parent;
}Binary_Tree_Node;


Binary_Tree_Node *ConstructCore(int *sPreorder, int *ePreorder, int *sInorder, int *eInorder);

Binary_Tree_Node *GetNext(Binary_Tree_Node *pNode){
    if(pNode == nullptr)
        return nullptr;

    Binary_Tree_Node *pNext = nullptr;

    if(pNode->right != nullptr)
    {
        while(pNode->right->left != nullptr){
            pNode->right = pNode->right->left;
        }
        pNext = pNode->right;
    }
    else if(pNode->parent != nullptr){
        Binary_Tree_Node *pCurrent = pNode;                       //临时量
        Binary_Tree_Node *pParent = pNode->parent;
        while(pCurrent == pParent->right && pParent != nullptr){   //判断当前父节点不为空且当前节点为右儿子
            pCurrent = pParent;
            pParent = pParent->parent;
        }
        pNext = pParent;
    }

    return pNext;
}

int main(){

    return 0;
}