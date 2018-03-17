#include <iostream>
#include <cstring>


using std::cout;
using std::endl;

typedef struct LISTNODE_{
    int val;
    LISTNODE_ *next;
}ListNode;

ListNode *MergeTwoSortedLsitNoRec(ListNode *pHead1, ListNode *pHead2){
    if(pHead1 == nullptr)
        return pHead2;
    else if(pHead2 == nullptr)
        return pHead1;

    ListNode *pMergedHead = nullptr;
    ListNode *pNode1 = pHead1;
    ListNode *pNode2 = pHead2;          //注意pN1和pN2需要赋初值，向前挪动
    if(pHead1->val < pHead2->val){
        pMergedHead = pHead1;
        pNode1 = pHead1->next;
    }
    else{
        pMergedHead = pHead2;
        pNode2 = pHead2->next;
    }

    ListNode *pTempHead = pMergedHead;
    while(pNode1 != nullptr && pNode2 != nullptr){
        if(pNode1->val < pNode2->val){
            pTempHead->next = pNode1;
            pTempHead = pNode1;
            pNode1 = pNode1->next;
        } else{
            pTempHead->next = pNode2;
            pTempHead = pNode2;
            pNode2 = pNode2->next;
        }
    }

    if(pNode1 != nullptr)
        pTempHead->next = pNode1;
    else
        pTempHead->next = pNode2;

    return pMergedHead;
}

int main(){
    return 0;
}

