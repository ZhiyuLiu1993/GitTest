#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>

using namespace std;

//求解number次打中sum环的种数
class Solution{
public:
    void ShootProblem_Solution1(int number, int sum, vector<int> &result, int &total)
    {
        if(sum < 0 || number * 10 < sum) //加number * 10 < sum非常重要，它可以减少大量的递归，类似剪枝操作
            return;
        if(number == 1) //最后一枪
        {
            if(sum <= 10) //如果剩余环数小于10，只要最后一枪打sum环就可以了
            {
//                for(unsigned i = 0; i < result.size(); i++)
//                    cout<<result[i]<<' ';
//                cout<<sum<<endl;
                ++total;
                return;
            }
            else
                return;
        }
        for(int i = 0; i <= 10; i++) //命中0-10环
        {
            result.push_back(i);
            ShootProblem_Solution1(number-1, sum-i, result, total); //针对剩余环数递归求解
            result.pop_back();
        }
    }
    void ShootProblem(int number, int sum)
    {
        int total = 0;
        vector<int> result;
        ShootProblem_Solution1(number, sum, result, total);
        cout<<"total nums = "<<total<<endl;
    }
};

int main()
{
    Solution a;
    a.ShootProblem(10, 90);
    return 0;
}
