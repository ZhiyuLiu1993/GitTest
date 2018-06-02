#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <sstream>

//给定一个源区间[x,y]和N个无序的目标区间[x1,y1] [x2,y2] ... [xn,yn]，判断源区间[x,y]是不是在目标区间内

using namespace std;

struct Line{
    int low;
    int high;
    bool operator<(const Line &l) const{
        return low < l.low;
    }
};

constexpr int MAXN = 10001;

Line lines[MAXN];   //目标区间

int ncnt = 0;    //合并后区间的个数

#define N 101
Line sl[N];

class Solution{
public:
    //用二分查找找出key所在的区间，以区间的low作为划分
    int GetIndex(int key){
        int low = 0;
        int high = ncnt;
        while( low <= high){
            int mid = low + ((high - low) >> 1);
            if(key >= lines[mid].low)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return high;
    }

    void find(int n, int k){
        sort(lines, lines + n);

        int last_high = lines[0].high;

        //原地合并   区间不存在完全覆盖
        for (int i = 0; i < n; ++i) {
            if(last_high >= lines[i].low)
                last_high = lines[i].high;
            else{
                lines[ncnt++].high = last_high;
                lines[ncnt].low = lines[i].low;
                last_high = lines[i].high;
            }
        }
        lines[ncnt].high = last_high;
        for (int j = 0; j < k; ++j) {
            int low = GetIndex(sl[j].low);
            int high = GetIndex(sl[j].high);
            //存在条件，low和high区间相同，不超过范围
            if(low == high && sl[j].high <= lines[high].high)
                cout<<"Yes"<<endl;
            else
                cout<<"No"<<endl;
        }
    }

};

int main() {
    Solution a;

    int n;
    int k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> lines[i].low >> lines[i].high;
    for (int i = 0; i < k; ++i)
        cin >> sl[i].low >> sl[i].high;
    a.find(n, k);


    return (0);
}

