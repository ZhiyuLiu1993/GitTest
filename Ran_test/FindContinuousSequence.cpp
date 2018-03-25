#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;


class Solution{
public:
    void FindContinuousSequence(int sum){
        if(sum < 3)
            throw std::exception();
        int small = 1;
        int big = 2;
        int middle = (1+sum)/2;
        int curSum = small + big;
        while (small < middle){
            if(curSum == sum){
                PrintNum(small, big);
                curSum -= small;
                ++small;
                ++big;
                curSum += big;
            } else if(curSum < sum){
                ++big;
                curSum += big;
            } else if(curSum > sum){
                curSum -= small;
                ++small;
            }
        }
    }

    void PrintNum(int small, int big){
        for (int i = small; i <= big; ++i) {
            cout<<i;
        }
        cout<<endl;
    }
};


int main(){
    Solution a;

    a.FindContinuousSequence(9);

    return 0;
}

