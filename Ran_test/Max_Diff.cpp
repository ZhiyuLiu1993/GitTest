#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>

using namespace std;

//在数组中，数字减去它右边的数字得到一个数对之差。求所有数对之差的最大值

class Solution{
public:
    int Max_Diff_Solution(int *pArray, int nLen)
    {
        if(pArray == NULL || nLen <= 1)
            return 0;
        //保存两个变量，一个保存当前最大值，一个保存差距最大值
        int f = 0;
        int m = pArray[0];
        for(int i = 1; i < nLen; i++)
        {
            f = max(f, m - pArray[i]);
            m = max(m, pArray[i]);
        }
        return f;
    }
};

int main()
{
    Solution a;
    return 0;
}
