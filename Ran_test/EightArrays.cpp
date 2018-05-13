#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>

//八卦阵相传是由诸葛亮创设的一种战斗队形和兵力部署，由八种阵势组成。
// 为了方便，采用矩阵来描述一个八卦阵，它由八个单阵组成，每个单阵由多个兵力区域组成形成一种阵势，
// 如下图所示，其中数字为一个兵力区域的士兵个数。假设单阵与单阵之间兵力区域不会相邻，
// 且单阵中每个兵力区域至少存在一个相邻兵力区域（注：相邻是指在其左上，正上，右上，右方，右下，正下，左下，左方与其相邻），
// 请用最快的速度计算出八个单阵中的兵力（士兵个数）的最大值和最小值。

//输入描述，例如：
//第一行输入是八阵图的行数。
//第二行输入是八阵图的列数。
//后续行输入每个区域兵力。每一行的数据中间使用空格分开，当前一行输入完成后回车输入下一行数据。
using namespace std;

struct Point{
    int x;
    int y;
    Point(int i, int j):x(i), y(j){}
};

const int N = 8;

class Solution{
public:
    void getMilitaryStrength(int A_size_row, int A_size_cols, int** A) {
        int mask[A_size_row][A_size_cols];
        memset(mask, 1, A_size_row * A_size_cols * sizeof(int));
        queue<Point*> que;

        int num = -1;
        int size[N];

        for (int i = 0; i < A_size_row; ++i) {
            for (int j = 0; j < A_size_cols; ++j) {
                if(A[i][j] && mask[i][j]){
                    Point *temp = new Point(i, j);
                    que.push(temp);
                    ++num;
                    size[num] = 0;
                    mask[i][j] = 0;
                }
                while(!que.empty()){
                    Point *cur = que.front();
                    que.pop();
                    int m = cur->x;
                    int n = cur->y;
//                    if(num == 0)
//                        cout<<"m:"<<m<<"; n:"<<n<<"; A:"<<A[m][n]<<endl;

                    size[num] += A[m][n];

                    if(m-1 >= 0 && n-1 >= 0 && mask[m-1][n-1] && A[m-1][n-1]){
                        Point *temp = new Point(m-1, n-1);
                        que.push(temp);
                        mask[m-1][n-1] = 0;
                    }
                    if(m-1 >= 0 && mask[m-1][n] && A[m-1][n]){
                        Point *temp = new Point(m-1, n);
                        que.push(temp);
                        mask[m-1][n] = 0;
                    }
                    if(m-1 >= 0 && n+1 < A_size_cols && mask[m-1][n+1] && A[m-1][n+1]){
                        Point *temp = new Point(m-1, n+1);
                        que.push(temp);
                        mask[m-1][n+1] = 0;
                    }
                    if(n-1 >= 0 && mask[m][n-1] && A[m][n-1]){
                        Point *temp = new Point(m, n-1);
                        que.push(temp);
                        mask[m][n-1] = 0;
                    }
                    if(n+1 < A_size_cols && mask[m][n+1] && A[m][n+1]){
                        Point *temp = new Point(m, n+1);
                        que.push(temp);
                        mask[m][n+1] = 0;
                    }
                    if(m+1 < A_size_row && n-1 >= 0 && mask[m+1][n-1] && A[m+1][n-1]){
                        Point *temp = new Point(m+1, n-1);
                        que.push(temp);
                        mask[m+1][n-1] = 0;
                    }
                    if(m+1 < A_size_row && mask[m+1][n] && A[m+1][n]){
                        Point *temp = new Point(m+1, n);
                        que.push(temp);
                        mask[m+1][n] = 0;
                    }
                    if(m+1 < A_size_row && n+1 < A_size_cols && mask[m+1][n+1] && A[m+1][n+1]){
                        Point *temp = new Point(m+1, n+1);
                        que.push(temp);
                        mask[m+1][n+1] = 0;
                    }
                }
            }
        }

        for_each(size, size+N, [](int &a){ cout<<a<<" "; });
        cout<<endl;
    }

};

int main() {
    Solution a;
    int res_size;
    int* res;

    int _A_rows = 0;
    int _A_cols = 0;
    scanf("%d", &_A_rows);
    scanf("%d", &_A_cols);

    int** _A = (int**)malloc(_A_rows*sizeof(int*));
    int _A_init_i=0;
    for(_A_init_i=0 ; _A_init_i<_A_rows ; ++_A_init_i)
    {
        _A[_A_init_i] = (int*)malloc(_A_cols*(sizeof(int)));
    }

    int _A_i, _A_j;
    for(_A_i = 0; _A_i < _A_rows; _A_i++) {
        for(_A_j = 0; _A_j < _A_cols; _A_j++) {
            int _A_item;
            scanf("%d", &_A_item);

            _A[_A_i][_A_j] = _A_item;
        }
    }

    a.getMilitaryStrength(_A_rows, _A_cols, _A);

    return (0);
}