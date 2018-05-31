#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <sstream>

//求一个二维数组中和最大的子矩阵

using namespace std;

class Solution{
public:
   //n为行 m为列
    int maxMatSum(int *A, int n, int m){
        int i;
        int j;
        int k;

        int **B = new int*[n+1];
        for( i = 0; i <= n; ++i){
            B[i] = new int[m];
        }
        //0行做哨兵
        for (j = 0; j < m; ++j) {
            B[0][j] = 0;
        }

        //将整个矩阵向右下移1位
        for (i = 0; i < n; ++i) {
            for (j = 0; j < m; ++j) {
                //A[i][j]应该等于A[i*m+j]
                B[i+1][j] = B[i][j] + A[i*m+j];
            }
        }

        int maxsum = 0x80000000;
        for(i = 1; i <= n; ++i){   //每行1-n  2-n  n-n
            for(j = i; j <= n; ++j){
                int start;
                int all;
                start = all = B[j][m-1] - B[i-1][m-1];
                for(k = m - 2; k >= 0; --k){   //每列从最左边开始
                    start = max(B[j][k] - B[i-1][k], start + B[j][k] - B[i-1][k]);
                    all = max(all, start);
                }
                if(all > maxsum){
                    maxsum = all;
                }
            }
        }

        for (i = 0; i <= n ; ++i) {
            delete [] B[i];
        }
        delete [] B;  //此处应该delete的也是数组
        return maxsum;
    }


};

int main() {
    Solution a;
    int A[] = {1, 3, 4, -5, 6, 7, 8, 4, 4, -10, 3, 1};
    cout<<a.maxMatSum(A, 4, 3)<<endl;

    return (0);
}

