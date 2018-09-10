#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <queue>

using namespace std;

//LeetCode 39

class Solution{
public:
    vector<vector<int>> res;

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> cur_num;
        find(candidates, target, cur_num, 0);

        return res;
    }

    void find(vector<int>& can, int target, vector<int> cur_num, int cur_idx){
        if(target == 0){
            res.push_back(cur_num);
            return;
        }

        for (int i = cur_idx; i < can.size(); ++i) {
            if(can[i] <= target){
                cur_num.push_back(can[i]);
                find(can, target-can[i], cur_num, i+1);   // i+1表示数字不可重复
//                find(can, target-can[i], cur_num, i);   // i表示数字可重复
                cur_num.pop_back();
            }
        }
    }

};


int main()
{
    Solution a;

    vector<int> candidates{2, 3, 6, 7};
    vector<vector<int>> res = a.combinationSum(candidates, 7);

    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            cout << res[i][j] << " ";
        }
        cout << endl;

    }

    return 0;
}

