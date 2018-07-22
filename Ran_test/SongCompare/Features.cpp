//
// Created by root on 7/19/18.
//

#include "Features.h"

int euclideanDistance(const std::vector<int> &s1, const std::vector<int> &s2){
    int distance = 0;
    int length = s1.size() > s2.size() ? s2.size() : s2.size();
    for (int i = 0; i < length; ++i) {
        if(s1[i] == s2[i])
            continue;
        else
            distance += abs(s1[i] - s2[i]);
    }
    return distance;
}

int hammingDistance(const std::vector<int> &s1, const std::vector<int> &s2){
    int distance = 0;
    int length = s1.size() > s2.size() ? s2.size() : s2.size();
    for (int i = 0; i < length; ++i) {
        if(s1[i] != s2[i])
            distance += 1;
        else
            continue;
    }
    return distance;
}

int editDistance(const std::vector<int> &s1, const std::vector<int> &s2){

    unsigned int n = s1.size();
    unsigned int m = s1.size();
    if (m == 0) return n;
    if (n == 0) return m;
    //Construct a matrix
    typedef std::vector<std::vector<int> >  Tmatrix;
    Tmatrix matrix(n + 1);
    for (int i = 0; i <= n; i++)  matrix[i].resize(m + 1);

    //step 2 Initialize

    for (int i = 1; i <= n; i++) matrix[i][0] = i;
    for (int i = 1; i <= m; i++) matrix[0][i] = i;

    //step 3
    for (int i = 1; i <= n; i++)
    {
        int si = s1[i - 1];
        //step 4
        for (int j = 1; j <= m; j++)
        {

            int sj = s2[j - 1];
            //step 5
            int cost = 0;
            if (si == sj){
                cost = 0;
            }
            else{
                cost = 1;
            }
            //step 6
            const int above = matrix[i - 1][j] + 1;
            const int left = matrix[i][j - 1] + 1;
            const int diag = matrix[i - 1][j - 1] + cost;
            matrix[i][j] = std::min(above, std::min(left, diag));

        }
    }//step7
    return matrix[n][m];

//    unsigned int s1_size = s1.size();
//    unsigned int s2_size = s2.size();
//
//    std::vector<std::vector<int>> mat(s1_size+1);
//    for (int i = 0; i < s1_size+1; ++i) {
//        mat[i].resize(s2_size+1);
//    }
//    for (int i = 1; i < s1_size+1; ++i) {
//        mat[i][0] = i;
//    }
//    for (int i = 1; i < s2_size+1; ++i) {
//        mat[0][i] = i;
//    }
//
//    int distance = 0;
//    int temp = 0;
//
//    for (int i = 1; i < s1_size+1; ++i) {
//        for (int j = 1; j < s2_size+1; ++j) {
//            if(s1[i-1] == s2[j-1])
//                distance = 0;
//            else
//                distance = 1;
//
//            temp = std::min(mat[i-1][j]+1, mat[i][j-1]+1);
//            mat[i][j] = std::min(temp, mat[i-1][j-1]+distance);
//        }
//    }
//
//    return mat[s1_size][s2_size];
}


