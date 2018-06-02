#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;


class Solution{
public:
    int GetMissingNumber(const int *numbers, int length){
        if(numbers == nullptr || length <= 0)
            return -1;
        int left = 0;
        int right = length - 1;
        while(left <= right){
            int mid = (left + right)/2;
            if(mid != numbers[mid]){
                if(mid == 0 || (mid > 0 && (mid-1 == numbers[mid-1])))
                    return mid;
                else if(mid - 1 != numbers[mid-1]){
                    right = mid - 1;
                }
            } else{
                left = mid + 1;
            }
        }
    }

};


int main(){
    Solution a;
    int arr[] = {1,2,3,4,5,6,7};
    cout<<a.GetMissingNumber(arr,7)<<endl;

    return 0;
}

