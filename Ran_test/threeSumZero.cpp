#include <iostream>

#include <vector>

#include <algorithm>

using namespace std;


class Solution{
public:

    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int len = nums.size();
        for (int k = 0; k < len; ++k) {
            if (nums[k] > 0)
                break;
            if (k > 0 && nums[k] == nums[k - 1])  //防止重复
                continue;
            int tmp = -nums[k];
            int i = k + 1;
            int j = len - 1;
            while (i < j) {
                if (nums[i] + nums[j] == tmp) {
                    res.push_back({nums[k], nums[i], nums[j]});
                    while (i < j && nums[i] == nums[i + 1])++i;
                    while (i < j && nums[j] == nums[j - 1])--j;
                    ++i;
                    --j;
                } else if (nums[i] + nums[j] < tmp) {
                    ++i;
                } else if (nums[i] + nums[j] > tmp) {
                    --j;
                }
            }
        }
        return res;
    }
};


int main()
{
    Solution tem;

    vector<int> a{0,0,0,0,0};
//    sort(a.begin(), a.end(), [](int tmp1, int tmp2){cout<<" "<<endl;
//        return tmp1 > tmp2;});
    vector<vector<int >> res = tem.threeSum(a);
    for (int i = 0; i < res.size(); ++i) {
        vector<int> res1 = res[i];
        for (int j = 0; j < res1.size(); ++j) {
            cout<<res1[j]<<" ";
        }
        cout<<endl;
    }
//    for_each(a.begin(), a.end(), [](const int &tmp){cout<<tmp<<" ";});

    return 0;

}