#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>
#include <map>

using namespace std;

//一个int数组，里面数据无任何限制，要求求出所有这样的数a[i]，其左边的数都小于等于它，右边的数都大于等于它。
class Solution{
public:
    void find_elements(int *arr, int len){
        if(arr == nullptr || len <= 0)
            return;

        int *p_min = new int[len];
        int max;
        int i;

        max = arr[0];
        p_min[len-1] = arr[len-1];

        for (i = len-2; i >= 0; --i) {
            p_min[i] = (p_min[i+1] < arr[i]) ? p_min[i+1] : arr[i];
        }

        if(arr[0] <= p_min[0])
            cout<< arr[0] << ' ';

        for (i = 1; i < len-1; ++i) {
            if(arr[i] >= max && arr[i] <= p_min[i+1])
                cout<< arr[i] << ' ';
            max = (max > arr[i]) ? max : arr[i];
        }

        if(arr[len-1] >= max)
            cout<< arr[i];
        cout<<endl;

        delete []p_min;
        p_min = nullptr;
    }

};

int main()
{
    Solution a;


    return 0;
}
