#include <iostream>

#include <vector>

#include <algorithm>
#include <list>

using namespace std;

//  Definition for singly-linked list.
 struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };

class Solution{
public:

    ListNode *swapPairs(ListNode *head) {
        ListNode *result;
        if(head != nullptr && head->next != nullptr)
            result = head->next;
        else
            return head;
        ListNode *tmp = result->next;
        result->next = head;
        head->next = tmp;
        ListNode *node = head;
        while(tmp && tmp->next){
            node->next = tmp->next;
            tmp->next = node->next->next;
            node->next->next = tmp;
            node = tmp;
            tmp = tmp->next;
        }
        return result;
    }
};


int main()
{



    return 0;

}