#include <iostream>

#include <vector>

#include <algorithm>
#include <list>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution{
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        if(head == nullptr || head->next == nullptr || k < 2) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *pre = dummy, *cur = head, *temp;
        int len = 0;
        while (head != nullptr) {
            len ++ ;
            head = head->next;
        }
        for (int i = 0; i < len / k; i ++ ) {
            for (int j = 1; j < k; j ++ ) {
                temp = cur->next;
                cur->next = temp->next;
                temp->next = pre->next;
                pre->next = temp;
            }
            pre = cur;
            cur = cur->next;
        }
        return dummy->next;
    }
};


int main()
{
    Solution a;

    ListNode head(1);
    ListNode n2(2);
    head.next = &n2;
    ListNode n3(3);
    n2.next = &n3;
    ListNode n4(4);
    n3.next = &n4;
    ListNode n5(5);
    n4.next = &n5;

    ListNode *res = a.reverseKGroup(&head, 2);
    for (int i = 0; i < 5; ++i) {
        cout<<res->val<<" "<<endl;
        res = res->next;
    }
    cout<<endl;

    return 0;

}