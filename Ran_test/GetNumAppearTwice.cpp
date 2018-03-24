#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;


class Solution{
public:
    void FindTwoNumsApperaOnce(int data[], int length, int &num1, int &num2){
        if(data == nullptr || length < 2)
            return;

        int resultExclusiveOR = 0;
        for (int i = 0; i < length; ++i)
            resultExclusiveOR ^= data[i];
        unsigned int index = FindFirstBitsIs1(resultExclusiveOR);
        num1 = num2 = 0;
        for (int j = 0; j < length; ++j) {
            if(IsBit1(data[j], index))
                num1 ^= data[j];
            else
                num2 ^= data[j];
        }
    }

    unsigned int FindFirstBitsIs1(int num){
        int indexbit = 0;
        while(((num&1) == 0) && indexbit < 8*sizeof(int)){
            num = num >> 1;
            ++indexbit;
        }

        return indexbit;
    }

    bool IsBit1(int num, unsigned int indexbits){
        num = num >> indexbits;
        return (num&1);    //注意&优先级很低，需要括号括起来
    }

};


int main(){
    Solution a;
    int arr[] = {1,1,2,3,3,4,5,5};

    int num1, num2;

    a.FindTwoNumsApperaOnce(arr, 8, num1, num2);

    cout<<num1<<"   "<<num2<<endl;

    return 0;
}

