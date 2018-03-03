#include <iostream>
/*
 *  将二叉查找树变成排序的双向链表
 * */

struct BSTreeNode{
    int value;
    BSTreeNode *m_pLeft;
    BSTreeNode *m_pRight;
};

void helper(BSTreeNode *&head, BSTreeNode *&tail, BSTreeNode *root){ //*&：指针引用，修改指针指向
    BSTreeNode *lt, *rh;
    if(root == NULL){
        head = NULL;
        tail = NULL;
        return;
    }
    helper(head, lt, root->m_pLeft); //head 与 tail和指针如果不是最后叶子节点则无用处
    helper(rh, tail, root->m_pRight);

    if(lt != NULL){
        lt->m_pRight = root;
        root->m_pLeft = lt;
    } else{
        head = root;
    }

    if(rh != NULL){
        root->m_pRight = rh;
        rh->m_pLeft = root;
    } else{
        tail = root;
    }
}

BSTreeNode *treeToLinkedList(BSTreeNode *root){
    BSTreeNode *head, *tail;
    helper(head, tail, root);
    return head;
}

void print(BSTreeNode *root){
    BSTreeNode *prt = root;
    while(prt != NULL){
       std::cout<<prt->value<<std::endl;
       prt = prt->m_pRight;
    }
}
void printD(BSTreeNode *root){ //todo:使用迭代而非递归的方法
    if(root == NULL){
        return;
    }
    std::cout<<root->value<<std::endl;
    printD(root->m_pLeft);
    printD(root->m_pRight);
}

int main() {
    BSTreeNode *root = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    BSTreeNode *ch1 = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    BSTreeNode *ch2 = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    BSTreeNode *ch3 = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    BSTreeNode *ch4 = (BSTreeNode *)malloc(sizeof(BSTreeNode));
    root->value = 5;
    ch1->value = 1;
    ch2->value = 2;
    ch3->value = 3;
    ch4->value = 4;

    root->m_pLeft = ch1;
    root->m_pRight = ch2;

    ch1->m_pLeft = ch3;
    ch1->m_pRight = ch4;
    ch2->m_pLeft = NULL;
    ch2->m_pRight = NULL;
    ch3->m_pLeft = NULL;
    ch3->m_pRight = NULL;
    ch4->m_pLeft = NULL;
    ch4->m_pRight = NULL;

    printD(root);

    BSTreeNode *temp = treeToLinkedList(root);
//    print(temp);

    return 0;
}
