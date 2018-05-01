#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

class Solution{
public:
    int trap(int A[], int n){
        if(A == nullptr || n <= 0)
            return 0;
        int lefttop = A[0];
        int righttop = A[n-1];
        int i = 1;
        int j = n - 2;
        int sum = 0;
        while(i <= j){
            if(lefttop > righttop){   //from outside to inside compression
                sum += max(0, righttop - A[j]);
                righttop = max(righttop, A[j]);
                --j;
            }else {
                sum += max(0, lefttop - A[i]);
                lefttop = max(lefttop, A[i]);
                ++i;
            }
        }
        cout<<sum<<endl;
        return sum;
    }
};

int main() {
//    int A[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int A[] = {2, 0, 2};
//    int A[] = {2, 0, 3, 0, 0, 1, 0, 0, 0, 4};
    int n = sizeof(A) / sizeof(int);
    Solution a;

    a.trap(A, n);

    return (0);
}