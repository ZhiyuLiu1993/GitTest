#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>

//从0, 1 ,2 ... n-1中随机选择m个数，每个数选中的概率要求一样，而且不允许重复

using namespace std;

class Solution{
public:
    //不适用n很大，m很小情况
    void random1(int n, int m){
        for (int i = 0; i < n; ++i) {
            if(rand() % (n - i) < m){  //当一直大于等于m时,不会插入，到后面n-i越来越小,一定能插入
                cout << i <<" ";
                --m;
            }
        }
    }

    //相对消耗空间  时间复杂度O(mlogm)
    void random2(int n, int m){
        set<int> s;
        while(s.size() < m){   //set保证元素不重复
            s.insert(rand() % n);
        }

        set<int>::iterator iter = s.begin();
        for(; iter != s.end(); ++iter)
            cout << *iter << " ";
    }

    //弄乱数组，将前m个元素排序输出
    void random3(int n, int m){
        int *x = new int[n];
        for (int i = 0; i < n; ++i) {
            x[i] = i;
        }

        for (int i = 0; i < m; ++i) { //随机产生i到n-1的数
            int j = i + rand() % (n - i);
            if(i != j){
                int temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }

        sort(&x[0], &x[m]);
        for (int k = 0; k < m; ++k) {
            cout << x[k] << " ";

        }
    }
};

int main() {
    Solution a;


    return (0);
}

