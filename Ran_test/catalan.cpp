#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>

using namespace std;

//卡塔兰数，是组合数学中一个常出现在各种计数问题中出现的数列。输入一个整数n，计算h(n)。
//其递归式如下：h(n)= h(0)*h(n-1)+h(1)*h(n-2) + ... + h(n-1)h(0) (其中n>=2，h(0) = h(1) = 1)
//该递推关系的解为：h(n)=C(2n,n)/(n+1) (n=1,2,3,...)

//应用
//1.括号匹配  f(2n) = f(0)*f(2n-2) + f(2)*f(2n - 4) + ... + f(2n - 4)*f(2) + f(2n-2)*f(0) = c(n)
//2.矩阵链乘   f(n) = f(1)*f(n-1) + f(2)*f(n-2) + f(3)*f(n-3) + f(n-1)*f(1) = c(n-1)
//3.进出栈序列  同1
//4.n个节点构成二叉树 f(n) = f(0)*f(n-1) + f(1)*f(n-2) + .......+ f(n-2)*f(1) + f(n-1)*f(0) = c(n)
//5.圆上选择2n个点，将这些点成对连接起来使得所得的n条线段不相交 同1
//6.将一个凸多边形划分成三角形区域的方法数 f(n)=f(2)*f(n-1) + f(3)*f(n-2) + ......f(n-2)*f(3) + f(n-1)*f(2)=c(n-2)
class Solution{
public:
    int catalan(int n){
        if(n <= 1)
            return 1;

        int *c = new int[n+1];

        c[0] = c[1] = 1;

        for (int i = 2; i <= n; ++i) {
            c[i] = 0;
            for (int j = 0; j < i; ++j) {
                c[i] += (c[j] * c[i-1-j]);
            }
        }

        int result = c[n];
        delete []c;
        return result;
    }

};

int main()
{
    Solution a;
    cout << a.catalan(3) <<endl;

    return 0;
}
