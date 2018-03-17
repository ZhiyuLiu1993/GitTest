#include <iostream>
#include <cstring>


using std::cout;
using std::endl;

typedef struct LISTNODE_{
    int m_value;
    LISTNODE_ *next;
}ListNode;

ListNode *ReverseListCore(ListNode *pNode, ListNode *pPrev){
    ListNode *pNext = pNode->next;
    pNode->next = pPrev;
     if(pNext != nullptr){
        pPrev =  pNode;
        pNode = pNext;
        return ReverseListCore(pNode, pPrev);
    } else
        return pNode;
}

ListNode *ReverseList(ListNode *pHead){
    if(pHead == nullptr)
        return nullptr;
    ListNode *pNext = pHead->next;
    ListNode *pPrev = nullptr;
    if(pNext != nullptr){
        pHead->next = pPrev;
        pPrev =  pHead;
        pHead = pNext;
        return ReverseListCore(pHead, pPrev);
    } else
        return pHead;
}

int main(){
    return 0;
}

