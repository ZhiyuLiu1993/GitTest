#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>

using namespace std;

//求出用1、2、5这三个数不同个数组合的和为100的组合数。

class Solution{
public:
    int C100_solution1(){
        int num = 0;
        for (int i = 0; i <= 100; ++i) {
            for (int j = 0; j <= 50 ; ++j) {
                for (int k = 0; k <= 20 ; ++k) {
                    num += ((i + 2 * j + 5 * k) == 100);
                }
            }
        }
        return num;
    }

    //求 x + 2y + 5z = 100解的个数。变化一下，x + 5z = 100 - 2y，这个式子表明 x + 5y只能是偶数。
    int C100_solution2(){
        int num = 0;
        //以z为循环变量, +2  是因为要包含自己,如下
        //组合总数为100以内的偶数+95以内的奇数+90以内的偶数+...+5以内的奇数+1
        for (int i = 0; i <= 100; i+=5) {
            num += (i + 2) / 2;
        }
        return num;
    }
};

int main()
{
    Solution a;
    cout << a.C100_solution1() << endl;
    cout << a.C100_solution2() << endl;
    return 0;
}
