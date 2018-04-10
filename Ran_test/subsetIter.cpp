#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Solution
{
public:
    //非递归解法
    void subsetIter(int *value, int size)
    {
        if (value == nullptr || size < 1) return;

        int *tmp = (int *)malloc(size * sizeof(int));
        memset(tmp, 0, size*sizeof(int));

        int num = (int)pow((double)2, (double)size);
        cout << "NULL" << endl;
        for (int i = 1; i < num; ++i)
        {
            for (int j = 0; j < size; ++j)//给输出标志赋值，二进制计算
            {
                if (tmp[j] == 1)
                    tmp[j] = 0;//逢二进一
                else if (tmp[j] == 0)
                {
                    tmp[j] = 1;
                    break;
                }
            }
            for (int j = 0; j < size; ++j)//比较输出标志，得出子集所包含元素
            {
                if (tmp[j] == 1) cout << value[j] << " ";
            }
            cout << endl;
        }
        delete tmp;
    }
    //递归解法
    void subsetRecursive(int *value, int m, int size, int *tmp)
    {
        if (m == -1)//此时标志位都已赋值，进行统计输出
        {
//            for (int i = size - 1; i >= 0; --i)
            for (int i = 0; i < size; ++i)
            {
                if (tmp[i] == 1) cout << value[i] << " ";//为1输出
            }
            cout << endl;
        }
        else
        {
            tmp[m] = 0;//先将此标志位赋值为0，即不输出
            subsetRecursive(value, m - 1, size, tmp);//递归到下一位
            tmp[m] = 1;//再将此标志位赋值为1，即输出
            subsetRecursive(value, m - 1, size, tmp);//递归到下一位
        }
    }
    void subset(int *value, int size)
    {
        if (value == NULL || size < 1) return;
        int *tmp =  (int *)malloc(size * sizeof(int));
        memset(tmp, 0, size * sizeof(int));

        subsetRecursive(value, size - 1, size, tmp);//从最高位开始

        free(tmp);
    }
};

int main(){
    Solution a;
    int arr[] = {1,2,3};

//    a.subsetIter(arr, sizeof(arr)/sizeof(int));


    a.subset(arr, sizeof(arr)/sizeof(int));

    return 0;
}