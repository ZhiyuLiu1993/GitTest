#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>

using namespace std;

//过河问题，一次最多过两人，只有一个手电筒
class Solution{
public:
    int CrossRiver(int *T, int n)
    {
        if(n == 2)       //剩两个人
            return T[1];
        else if(n == 3)  //剩三个人
            return T[0] + T[1] + T[2];
        else
        {
            //两种方案，具体哪种方案需要视情况而定
            //方案1，最快和次快先过去，最快回来，最慢和次慢过去，次快回来
            //方案2，最快和最慢过去，最快回来，最快和次慢过去，最快回来
            int t1 = T[0] + T[1] + T[1] + T[n-1];   //方案1
            int t2 = T[0] + T[0] + T[n-1] + T[n-2]; //方案2
            int t = t1 > t2 ? t2 : t1;

            //每次递归减少两个最慢的
            return CrossRiver(T, n - 2) + t;
        }
    }

    int CrossRiverRecur(int *T, int n)
    {
        if(n == 1)         //一个旅行者
            return T[0];
        else if(n == 2)    //两个旅行者
            return T[0] > T[1] ? T[0]: T[1];
        else               //多个，递归求解
        {
            sort(T, T + n);//由快到慢排个序
            return CrossRiver(T, n);
        }
    }

    int CrossRiverIter(int *T, int n){
        if(n == 1)         //一个旅行者
            return T[0];
        else if(n == 2)    //两个旅行者
            return T[0] > T[1] ? T[0]: T[1];
        sort(T, T + n);
        int sum = 0;
        while(n){
            if(n == 2){
                sum += T[1];
                break;      //***退出循环条件
            }else if(n == 3){
                sum += T[0] + T[1] + T[2];
                break;      //***退出循环条件
            }else{
                int t1 = T[0] + T[1] + T[1] + T[n-1];   //方案1
                int t2 = T[0] + T[0] + T[n-1] + T[n-2]; //方案2
                sum += (t1 > t2 ? t2 : t1);
                n -= 2;
            }
        }

        return sum;
    }
};

int main()
{
    int T[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Solution a;

    cout << a.CrossRiverRecur(T, 9) << endl;
    cout << a.CrossRiverIter(T, 9) << endl;
    return 0;
}
