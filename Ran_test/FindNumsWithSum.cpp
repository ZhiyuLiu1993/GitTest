#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;


class Solution{
public:
    bool FindNumsWithSum(int data[], int length, int sum, int &num1, int &num2){
        if(data == nullptr || length < 2)
            throw std::exception();
        int start = 0;
        int end = length - 1;
        while (start < end){
            int temp = data[start] + data[end];
            if(temp > sum)
                --end;
            else if(temp < sum)
                ++start;
            else{
                num1 = data[start];
                num2 = data[end];
                return true;
            }
        }
        return false;
    }
};


int main(){
    Solution a;
    int arr[] = {1,2,3,4,6,9};

    int num1;
    int num2;

    if(a.FindNumsWithSum(arr, 6, 80, num1, num2))
        cout<<num1<<" "<<num2<<endl;

    return 0;
}

