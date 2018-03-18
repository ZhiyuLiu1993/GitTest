#include <iostream>
#include <cstring>
#include <queue>


using std::cout;
using std::endl;
using std::queue;

typedef struct TREENODE_ {
    int val;
    struct TREENODE_ *left;
    struct TREENODE_ *right;
}TreeNode;

void MirrorIteratively(TreeNode *pNode){
    if(pNode == nullptr)
        return;

    queue<TreeNode *> que;
    que.push(pNode);

    while(!que.empty()){
        TreeNode *pTemp = que.front();
        que.pop();
        if(pTemp->left == nullptr && pTemp->right == nullptr)
            continue;

        TreeNode *pChange = pTemp->left;
        pTemp->left = pTemp->right;
        pTemp->right = pChange;

        if(pTemp->left != nullptr)
            que.push(pTemp->left);
        if(pTemp->right != nullptr)
            que.push(pTemp->right);
    }

}

int main(){
    return 0;
}

