#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <sstream>

//构建乘积数组

using namespace std;

class Solution{
public:
    void productArray(vector<int> &a, vector<int> &b){
        int length = a.size();
        if(length > 1){
            b[0] = 1;
            for (int i = 1; i < length; ++i) {
                b[i] = b[i-1] * a[i-1];
            }
            int temp = 1;
            for (int j = length - 2; j >= 0; --j) {
                temp *= a[j+1];
                b[j] *= temp;
            }
        }
    }


};

int main() {
    Solution a;
    vector<int> A = {1, 2, 3, 4, 5};
    vector<int> B;
    B.resize(A.size());
    a.productArray(A, B);
    for(auto const &i: B){
        cout<<i<<" "<<endl;
    }

    return (0);
}

