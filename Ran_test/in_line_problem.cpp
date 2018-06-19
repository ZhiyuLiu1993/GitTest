#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>

using namespace std;

//12个高矮不同的人，排成两排，每排必须是从矮到高排列，而且第二排比对应的第一排的人高，问排列方式有多少种
class Solution{
public:
    //对于i号，如果第一排与第二排的人数一样，那么他只能排在第一排；如果第一排的人数大于第二排
    // 那么他可以排在第一排或者第二排。递归终止的条件是第一排或第二排排满了。
    //假定已按高矮顺序排好
    void in_line_problem(int firstFree, int secondFree, int num, int &total_num){
        if(firstFree == num/2 || secondFree == num/2){ //其中一排无剩余位置
            ++total_num;
            return;
        }

        if(firstFree == secondFree) //第1排人数与第2排人数一样
            in_line_problem(firstFree+1, secondFree, num, total_num); //只排在第1排
        else{
            in_line_problem(firstFree + 1, secondFree, num, total_num);
            in_line_problem(firstFree, secondFree + 1, num, total_num);
        }
    }
};

int main()
{
    Solution a;

    int total_num = 0;

    a.in_line_problem(0, 0, 12, total_num);

    cout<<total_num<<endl;

    return 0;
}
