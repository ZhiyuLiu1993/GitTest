#include <iostream>
#include <vector>
#include <limits>

using namespace std;
//寻找数组中的背叛者，距离数组值（所有数之和的一半）差距最大的是traitor，每次去除数组中离数组值最近的，3,5 数组值4,3更近
class Solution{
public:
    int Traitor(int group[], int length){
        int median;
        for(int i = 0; i < length-1; ++i){
            median = 0;
            for (int j = 0; j < length; ++j) {
                median += group[j];
            }
            median = median>>1;
            int max = 0;
            int node = 0;
            int k = 0;
            for (k = 0; k < length; ++k) {
                if(group[k] == 0)
                    continue;
                max = abs(group[k]-median);
                node = k;
                break;
            }
            for (++k; k < length; ++k) {
                if(group[k] == 0)
                    continue;
                if(max > abs(group[k]-median)){
                    max = abs(group[k]-median);
                    node = k;
                }
            }
            group[node] = 0;
        }

        for (int l = 0; l < length; ++l) {
            if(group[l])
                return group[l];
        }
    }
};

int main() {
    Solution a;

    int n;
    cin>>n;
    int group[n];
    for (int i = 0; i < n; ++i) {
        cin>>group[i];
    }

    cout<<a.Traitor(group, n)<<endl;

    return 0;
}