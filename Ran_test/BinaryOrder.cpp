#include <iostream>
#include <stack>
#include <queue>

typedef struct BINARY_TREE_{
    int value;
    BINARY_TREE_ *left;
    BINARY_TREE_ *right;
}Binary_Tree;

void iterativePreorder(Binary_Tree *root){
    std::stack<Binary_Tree *> sta;
    Binary_Tree *node;
    if(root != nullptr){
        sta.push(root);
        while(!sta.empty()){
            node = sta.top();
            sta.pop();
            std::cout<<node->value<<std::endl;
            if(node->right != nullptr){
                sta.push(node->right);
            }

            if(node->left != nullptr){
                sta.push(node->left);
            }
        }
    }
}

void iterativeInorder(Binary_Tree *root){
    std::stack<Binary_Tree *> sta;
    Binary_Tree *node = root;
    while (node != nullptr || sta.size() > 0){
        while(node != nullptr){
            sta.push(node);
            node = node->left;
        }

        if(sta.size() > 0){
            node = sta.top();
            sta.pop();
            std::cout<<node->value<<std::endl;
            node = node->right;
        }
    }
}

//单栈实现二叉树后序遍历
void iterativePostorder(Binary_Tree *root){
    std::stack<Binary_Tree *> sta;
    Binary_Tree *node = root;
    Binary_Tree *preNode = nullptr;
    while(node != nullptr || sta.size()>0){
        while(node != nullptr){
            sta.push(node);
            node = node->left;
        }
        if(sta.size() > 0){
            Binary_Tree *temp = sta.top()->right;
            //根节点被访问：无右子树或右子树已被访问
            if(temp == nullptr || temp == preNode){
                node = sta.top();
                sta.pop();
                std::cout<<node->value<<std::endl;
                preNode = node;  //记录刚被访问的节点
                node = nullptr;
            } else{
                node = temp;  //右子树
            }
        }
    }
}

//双栈实现二叉树后序遍历
void iterativePostorder2(Binary_Tree *root){
    std::stack<Binary_Tree *> sta;
    std::stack<Binary_Tree *> temp;
    Binary_Tree *node = root;
    while(node != nullptr || sta.size() > 0){
        while(node != nullptr){ //当前结点及其右侧节点入栈
            sta.push(node);
            temp.push(node);
            node = node->right;
        }

        if(sta.size() > 0){  //处理栈顶的左子树
            node = sta.top();
            sta.pop();
            node = node->left;
        }
    }
    while(temp.size() > 0){
        node = temp.top();
        temp.pop();
        std::cout<<node->value<<std::endl;
    }
}

//层序遍历,使用队列，先入队左子树
void layerTraversal(Binary_Tree *root){
    std::queue<Binary_Tree *> que;
    if(root != nullptr){
        que.push(root);
        while(!que.empty()){
            Binary_Tree *curNode = que.front();
            que.pop();
            std::cout<<curNode->value<<std::endl;

            if(curNode->left != nullptr){
                que.push(curNode->left);
            }

            if(curNode->right != nullptr){
                que.push((curNode->right));
            }
        }
    }
}

//加入注释
//test 函数
int main(){

}
