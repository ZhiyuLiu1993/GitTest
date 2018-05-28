#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <sstream>

//问题描述：输入两个整数n和m，从数列1，2.......n中随意取几个数，使其和等于m，要求将其中所有的可能组合列出来
//递归:效率可能低了点。假设问题的解为F(n, m)，可分解为两个子问题 F(n-1, m-n)和F(n-1, m)。
//对这两个问题递归求解，求解过程中，如果找到了符合条件的数字组合，则打印出来。
//循环:其实就是枚举所有组合。对于n ，组合数应该为2^n。我们可以用一个数字 i 来表示组合。
//如果i = 5，其二进制形式为101，相应的组合为{1, 3}。也就是说，二进制的每一位都代表一个数字，bit0代表数字1，bit1代表数字2，依次类推。
//当某位为1，表示选中了该位所表示的数字。
using namespace std;


class Solution{
public:
    void BagProblem_Solution_Recur(int n, int m, int *flag, int len)
    {
        if(n < 1 || m < 1)
            return;

        if(n < m)
        {
            flag[n-1] = 1;
            BagProblem_Solution_Recur(n-1, m-n, flag, len); //选了n
            flag[n-1] = 0;
            BagProblem_Solution_Recur(n-1, m, flag, len);   //不选n
        }
        else
        {
            flag[m-1] = 1;  //n>=m，选中m即可
            for(int i = 0; i < len; i++)
            {
                if(flag[i] == 1)
                    cout<<i+1<<' ';
            }
            cout<<endl;
            flag[m-1] = 0; //不选m，继续递归。比如n = 10,m = 8，求出{1, 7}后，仍需继续，{1,3,4} {1,2,5}都是解
            BagProblem_Solution_Recur(m-1, m, flag, len);
        }
    }

    void BagProblem_Solution_Itera(int n, int m)
    {
        if(n < 1|| m < 1)
            return;
        if(n > m)
            n = m;

        int num = 1<<n;               //枚举次数
        for(int i = 1; i < num; i++)  //枚举所有情况
        {
            int sum = 0;
            int j, k;
            for(j = i, k = 1; j != 0; j>>=1, k++) //针对每种情况求和，判断是否满足条件
            {
                if(j&1)
                    sum += k;
            }
            if(sum == m) //如果满足，打印结果
            {
                for(j = i, k = 1; j != 0; j>>=1, k++)
                {
                    if(j&1)
                        cout<<k<<' ';
                }
                cout<<endl;
            }
        }
    }

};

int main() {
    Solution a;


    return (0);
}
