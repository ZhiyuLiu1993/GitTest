#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <sstream>


using namespace std;

class Solution{
public:
     int longestPalindromeSubsequence(string &str){
        int n = str.size();
        vector<vector<int>> dp(n, vector<int> (n));

        for(int j = 0; j < n; ++j){
            dp[j][j] = 1;
            for(int i = j - 1; i >= 0; --i){
                if(str[i] == str[j])
//                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                     dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]; //NumofPalindromeSubsequence
                else
//                    dp[i][j] = dp[i+1][j-1] + 2;
                    dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1] //NumofPalindromeSubsequence
                               + dp[i+1][j-1] + 1;
            }
        }
         return dp[0][n-1];
     }
};

int main() {
    string str("aba");
    Solution a;
    cout<<a.longestPalindromeSubsequence(str)<<endl;

    return (0);
}