#include <iostream>

//根据前序和中序遍历结果重建二叉树
//使用递归的方式构建

typedef struct BINARY_TREE_NODE_{
    int value;
    BINARY_TREE_NODE_ *left;
    BINARY_TREE_NODE_ *right;
}Binary_Tree_Node;


Binary_Tree_Node *ConstructCore(int *sPreorder, int *ePreorder, int *sInorder, int *eInorder);

Binary_Tree_Node *construct(int *preorder, int *inorder, int length){
    if(preorder == nullptr || inorder == nullptr || length < 1)
        return nullptr;
    return ConstructCore(preorder, preorder+length-1, inorder, inorder+length-1);
}

Binary_Tree_Node *ConstructCore(int *sPreorder, int *ePreorder, int *sInorder, int *eInorder){
    int rootValue = sPreorder[0];
    Binary_Tree_Node *root = new Binary_Tree_Node();
    root->value = rootValue;
    root->left = root->right = nullptr;

    if(sPreorder == ePreorder){
        if(*sPreorder == *ePreorder)
            return root;
        else{
            std::cout<<"invalid input"<<std::endl;
            return nullptr;
        }
    }

    int *rootInorder = sInorder;
    while(rootInorder <= eInorder && *rootInorder != rootValue)
        ++rootInorder;

    if(*rootInorder != rootValue){
        std::cout<<"invalid input"<<std::endl;
        return nullptr;
    }

    int leftLength = rootInorder -sInorder;
    int *leftPreorderE = sPreorder + leftLength;

    if(leftLength > 0){
        root->left = ConstructCore(sPreorder + 1, leftPreorderE, sInorder, rootInorder - 1);

    }
    if(leftLength < ePreorder - sPreorder){
        root->right = ConstructCore(leftPreorderE + 1, ePreorder, rootInorder + 1, eInorder);
    }

    return root;
}

int main(){
    int preOrder[] = {1, 2, 4, 7, 3, 5, 6, 8};
    int inOrder[] = {4, 7, 2, 1, 5, 3, 8, 6};
    Binary_Tree_Node *root = construct(preOrder, inOrder, 8);

    return 0;
}