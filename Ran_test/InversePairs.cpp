#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;

//求出数组内部逆序对，采用归并排序的方法

class Solution{
public:
    int InversePairs(int *data, int length){
        if(data == nullptr || length < 0)
            return 0;
        int *copy = new int[length];

        for (int i = 0; i < length; ++i) {
            copy[i] = data[i];
        }

        int count = InversePairsCore(data, copy, 0, length-1);

        delete[] copy;
        return count;
    }

    int InversePairsCore(int *data, int *copy, int start, int end){
        if(start == end){
            return 0;
        }

        int length = (end-start)/2;

        int left = InversePairsCore(copy, data, start, start+length);    //copy和data需要交叉
        int right = InversePairsCore(copy, data, start+length+1, end);

        int i = start + length;
        int j = end;
        int indexCopy = end;
        int count = 0;
        while (i>=start && j>=start+length+1){
            if(data[i] > data[j]){
                copy[indexCopy--] = data[i--];
                count += j-start-length;  //j-start-length-1+1
            } else{
                copy[indexCopy--] = data[j--];
            }
        }

        for (; i >= start; --i)
            copy[indexCopy--] = data[i];
        for (; j >= start+length+1; --j)
            copy[indexCopy--] = data[j];

        return count+left+right;
    }

};


int main(){
    Solution a;

    int arr[4] = {7, 5, 6, 4};

    cout<<a.InversePairs(arr, 4)<<endl;

    return 0;
}

