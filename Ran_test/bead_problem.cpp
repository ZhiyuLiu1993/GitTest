#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>

using namespace std;

//一串首尾相连的珠子(n个)，有c种颜色，取出其中一段，要求包含所有N种颜色，并使长度最短
class Solution{
public:
    bool bead_problem(int *p_bread, int n, int c, int &from, int &to){
        if(p_bread == nullptr || n < c)
            return false;

        int count[c] = {0};
        int min_len = n + 1;
        int i = 0;
        int j = -1;
        int color_count = 0;

        while(j < n - 1){ //j 循环条件不能等于 n-1 下次判断不算入此位置
            if(++count[p_bread[i]] == 1 && ++color_count == c){
                //减少当前颜色数量，此颜色仍然还有
                //上一次j还在链中，这次需要加1
                for (j = j + 1; j < n && --count[p_bread[j]]; ++j) ;

                if(j == n) //j 加到了末尾  j不会转一圈
                    --j;

                // n-(j-i-1)
                int len = (j > i) ? i-j+n+1 : i-j+1;

                if(len < min_len){
                    from = j; //start
                    to = i;
                    min_len = len;
                }
                --color_count;
            }

            //考虑环
            i = (i+1) % n;

            //没有找到
            if(i == 0 && j == -1)
                break;
        }
        return min_len != n+1;
    }
};

int main()
{
    Solution a;

    int bead[] = {3,3,4,0,1,1,2,2,3,4,0,1,1,2,3,4};
    int from, to;
    int n = sizeof(bead)/sizeof(int);
    if(a.bead_problem(bead, n, 5, from, to)){
        for (int i = from; i != to; i = (i+1) % n)
            cout << bead[i] << ' ';
        cout << bead[to] << endl;
    }

    return 0;
}
