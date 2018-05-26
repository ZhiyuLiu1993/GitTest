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
    void Permutation(string Str, int begin){
        if(begin == Str.size() - 1){   //-1 才能与下面的+1匹配，否则此条件永远不满足
            cout<<Str<<endl;
        }
        else{
            for(int i = begin+1; i < Str.size(); ++i){   //此处+1  计算的是原字母不在其原始位置上的排列    最终begin就不会到size大小
                char temp = Str[i];
                Str[i] = Str[begin];
                Str[begin] = temp;

                Permutation(Str, begin+1);

                temp = Str[i];
                Str[i] = Str[begin];
                Str[begin] = temp;
            }
        }
    }

};

int main() {
    Solution a;

    string str("abc");

    a.Permutation(str, 0);

    return (0);
}
