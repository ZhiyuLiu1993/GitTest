#include <iostream>
#include <vector>
#include <limits>

using namespace std;

//一个n x m的矩阵M，每个元素 M[i][j] ( 0<= i<= n - 1 && 0 <= j <= m - 1) 表示从（i，j）位置出发，跳跃的最远距离；每次跳跃可以选择向右，上，下三个方向，注意： 上、下跳时不能走回头路。
//现在可以选择从最左边一列任何位置出发，一直跳到最右边一列任何位置，这都代表到达终点。求到达终点所需的最小跳数，如果无法到达，返回 -1。
/*请完成下面这个函数，实现题目要求的功能*/
///warning：注意在一列加减可能会两个下标来回跳动，造成栈溢出×××
///如果可以走任一步，考虑从最后一列开始计算，先所有点初始化为INT_MAX，每个点到第一个点依次计算，根据其含有值进行上下右的范围判断
/******************************开始写代码******************************/

int right(const vector<vector<int>> &matrix, int n, int m, int i, int j, int count);
int up(const vector<vector<int>> &matrix, int n, int m, int i, int j, int count);
int down(const vector<vector<int>> &matrix, int n, int m, int i, int j, int count);


int right(const vector<vector<int>> &matrix, int n, int m, int i, int j, int count){
    int min_count = INT32_MAX;
    int rcount = 0;
    int ucount = 0;
    int dcount = 0;
    if(j + matrix[i][j] >= m-1)
        return (count+1);
    else if(matrix[i][j+matrix[i][j]] == 0)
        return INT32_MAX;
    else{
        rcount = right(matrix, n, m, i, j+matrix[i][j], 1);
        ucount = up(matrix, n, m, i, j+matrix[i][j], 1);
        dcount = down(matrix, n, m, i, j+matrix[i][j], 1);
    }
    if(rcount < min_count)
        min_count = rcount;
    if(ucount < min_count)
        min_count = ucount;
    if(dcount < min_count)
        min_count = dcount;
    if(min_count == INT32_MAX)
        return INT32_MAX;
    return min_count + count;
}

int up(const vector<vector<int>> &matrix, int n, int m, int i, int j, int count){
    int min_count = INT32_MAX;
    int rcount = 0;
    int ucount = 0;
    int dcount = 0;
    if(i - matrix[i][j] < 0 || matrix[i - matrix[i][j]][j] == matrix[i][j])
        return INT32_MAX;
    else if(matrix[i - matrix[i][j]][j] == 0)
        return INT32_MAX;
    else{
        rcount = right(matrix, n, m, i - matrix[i][j], j, 1);
        ucount = up(matrix, n, m, i - matrix[i][j], j, 1);
        dcount = down(matrix, n, m, i - matrix[i][j], j, 1);
    }
    if(rcount < min_count)
        min_count = rcount;
    if(ucount < min_count)
        min_count = ucount;
    if(dcount < min_count)
        min_count = dcount;
    if(min_count == INT32_MAX)
        return INT32_MAX;
    return min_count + count;
}

int down(const vector<vector<int>> &matrix, int n, int m, int i, int j, int count){
    int min_count = INT32_MAX;
    int rcount = 0;
    int ucount = 0;
    int dcount = 0;
    if(i + matrix[i][j] > n-1 || matrix[i + matrix[i][j]][j] == matrix[i][j])
        return INT32_MAX;
    else if(matrix[i + matrix[i][j]][j] == 0)
        return INT32_MAX;
    else{
        rcount = right(matrix, n, m, i + matrix[i][j], j, 1);
        ucount = up(matrix, n, m, i + matrix[i][j], j, 1);
        dcount = down(matrix, n, m, i + matrix[i][j], j, 1);
    }
    if(rcount < min_count)
        min_count = rcount;
    if(ucount < min_count)
        min_count = ucount;
    if(dcount < min_count)
        min_count = dcount;
    if(min_count == INT32_MAX)
        return INT32_MAX;
    return min_count + count;
}

int jump(const vector<vector<int>> &matrix, int n, int m) {
    if(m < 2)
        return 0;
    int count = 0;
    int min_count = INT32_MAX;
    for (int k = 0; k < n; ++k) {
        int rcount = right(matrix, n, m, k, 0, count);
        if(min_count > rcount)
            min_count = rcount;
    }
    if(min_count == INT32_MAX)
        return -1;
    return min_count;
}

/******************************结束写代码******************************/

int main() {
    int n, m;
    cin >> n >> m;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    vector<vector<int>> matrix;
    for (int i = 0; i < n; i++) {
        vector<int> row;
        for (int j = 0; j < m; j++) {
            int e;
            cin >> e;
            row.push_back(e);
        }

        matrix.push_back(row);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    cout << jump(matrix, n, m) << endl;

    return 0;
}