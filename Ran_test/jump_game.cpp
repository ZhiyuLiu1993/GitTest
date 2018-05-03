#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>


using namespace std;

class Solution{
public:
    int jump_game(int A[], int n){
        int dp[n];
        memset(dp, 0, n * sizeof(int));   //  third param is byte
        for (int i = 0; i < n; ++i) {
            int maxPosition = min(i + A[i], n - 1);
            for (int j = i + 1; j <= maxPosition; ++j) {
                if(dp[j] == 0)
                    dp[j] = dp[i] + 1;
            }
            if(dp[n-1]) break;
        }
        return dp[n-1];
    }
};

int main() {
    Solution a;
    int A[] = {2, 3, 1, 1, 2};
    cout<<a.jump_game(A, sizeof(A)/sizeof(int))<<endl;

    return (0);
}