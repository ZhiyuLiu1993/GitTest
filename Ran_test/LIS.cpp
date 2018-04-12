#include <iostream>

#include <vector>

#include <algorithm>

using namespace std;



class Solution{
public:
    int LIS(int *arr, int n){    //B只存对应长度子序列末尾，不是整个子序列
        int len = 1;
        int B[n];
        B[0] = arr[0];
        int i;
        int pos = 0;
        for (i = 0; i < n; ++i) {
            if(arr[i] > B[len-1])
                B[len++] = arr[i];
            else{
                pos = BinarySearch(B, len, arr[i]);
                B[pos] = arr[i];
            }
        }
        return len;
    }

    int BinarySearch(int *b, int len, int w){
        int left = 0;
        int right = len - 1;
        while(left < right){
            int mid = left + ((right - left)>>1);
            if(b[mid] > w)
                right = mid - 1;
            else if(b[mid] < w)
                left = mid + 1;
            else
                return mid;
        }
        return left;
    }

    int LisDP(int *arr, int n){ //动态规划版本
        int dp[n];
        int max = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
               if(arr[i] > arr[j]){  //i > j才能在此基础上累加
                   dp[i] = dp[i] > (dp[j]+1) ? dp[i]:(dp[j]+1);
                   if(dp[i] > max)
                       max = dp[i];
               }
            }
        }
        return max;
    }
};


int main()
{
    int a[] = {1, 3, 4, 0, 5, 6, 7, 8};
    Solution res;
//    res.LIS(a, sizeof(a)/sizeof(int));
    cout<<res.LisDP(a, sizeof(a)/sizeof(int))<<endl;
    return 0;

}