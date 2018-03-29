#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using std::cout;
using std::endl;
using std::vector;
using std::unordered_set;

//给1-9中的数，选择k个，组成k位数，输出每位不重复的数

class Solution{
public:
    vector<int> output;
    vector<int> selectK(vector<int> input, int k){
        if(k>9 || k<0 || k > input.size())
        {
            return output;
        }
        unordered_set<int> set;
        for(int i=0;i<input.size();i++) {
            int temp = input[i];
            if(set.count(temp) || temp>9||temp<1)
            {
                output.clear();
                return output;
            }
            else
                set.insert(temp);

        }
        selectKcore(input, k, 0);
        return output;
    }

    void selectKcore(vector<int> &input, int k, int sum) {
        if(k == 0){
            output.push_back(sum);
            return;
        }
        for (int i = 0; i < input.size(); ++i) {
            int num = input[i];
            if(!num)
                continue;
            input[i] = 0;
            selectKcore(input, k-1, sum*10+num);
            input[i] = num;
        }
    }

};


int main(){
    vector<int> vec{1,2,3,4};
    Solution a;

    vector<int> result = a.selectK(vec, 3);
    for(auto a: result)
        cout<<a<<endl;

    return 0;
}

