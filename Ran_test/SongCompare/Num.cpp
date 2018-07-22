//
// Created by root on 7/20/18.
//

#include "Num.h"

#include <iostream>

static void SortRows(const Eigen::MatrixXf &input, int n, int *output, int m, int row);
static void SortRows2(const Eigen::MatrixXf &input, int n, int *output, int m, int row);
//static void SortCols(const Eigen::MatrixXf &input, int *output, int rows, int cols, int col);
static void SortCols2(const Eigen::MatrixXf &input, Eigen::MatrixXi &output, int row);

Eigen::MatrixXi argsort(const Eigen::MatrixXf &input, int type){
    int rows = input.rows();
    int cols = input.cols();
    Eigen::MatrixXi output(rows, cols);
//    Eigen::Matrix<int, rows, cols, Eigen::RowMajor> output(3, 4);
    if(!type){   //按列
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                output(i, j) = i;
//                std::cout <<  *(output.data()+k);
//                *(output.data()+i*cols+j) = i;
            }
        }
//        for (int k = 0; k < output.size(); ++k) {
//            std::cout <<  *(output.data()+k);
//        }
//        std::cout << std::endl;
//        std::cout << output << std::endl;
        for (int i = 0; i < cols; ++i) {
//            int *id = output.data();
//            Sort(input, cols, id, cols, i);
//            SortCols(input, output.data()+i, rows, cols, i);
            SortRows2(input, rows, output.data()+i*rows, rows, i);
        }

    } else{      //按行
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                output(i, j) = j;
            }
        }

//        for (int k = 0; k < output.size(); ++k) {
//            std::cout <<  *(output.data()+k);
//        }
//        std::cout << std::endl;

//        std::cout << output << std::endl;
        for (int i = 0; i < rows; ++i) {
//            int *id = output.data();
//            Sort(input, cols, id, cols, i);
//            for (int j = 0; j < cols; ++j) {
//                std::cout <<  *(output.data()+i*cols+j);
//            }
//            std::cout << std::endl;

//            int *id = output.data();
            SortCols2(input, output, i);
//            SortRows(input, cols, id+i*cols, cols, i);
        }
    }
//    std::cout << output << std::endl;
//    int *data = output.data();
//    for (int i = 0; i < output.size(); ++i) {
//        std::cout << data[i];
//    }
//    std::cout<<std::endl;
    return output;
}

void SortOr(int a[], int n, int id[], int m) {
    if (m > 1) {
        int i = 0;
        int j = m - 1;
        int tmp = id[i];
        while (i < j) {
            while (j > i && a[id[j]] > a[tmp])
                --j;
            if (j > i)
                id[i++] = id[j];  //只改变索引顺序
            while (j > i && a[id[i]] < a[tmp])
                ++i;
            if (j > i)
                id[j--] = id[i];  //只改变索引顺序
        }
        id[i] = tmp;
        SortOr(a, n, id, i);
        SortOr(a, n, id + i + 1, m - i - 1);
    }
}

//因为Matrix的矩阵数据是按列存储的,所以在排序计算索引时时使用不同的算法，按列时使用递归的快排
//按列,选择排序,对应与存储按列
static void SortRows2(const Eigen::MatrixXf &input, int n, int *output, int m, int row) {
    if (m > 1) {
        int i = 0;
        int j = m - 1;
        int tmp = output[i];
        while (i < j) {
            while (j > i && input(output[j], row) > input(tmp, row))
                --j;
            if (j > i)
                output[i++] = output[j];  //只改变索引顺序
            while (j > i && input(i, row) < input(tmp, row))
                ++i;
            if (j > i)
                output[j--] = output[i];  //只改变索引顺序
        }
        output[i] = tmp;
        SortRows2(input, n, output, i, row);
        SortRows2(input, n, output+i+1, m-i-1, row);
    }
//    for (int j = 0; j < m; ++j) {
//        std::cout << output[j];
//    }
//    std::cout << std::endl;
}
//实现两种类型sort,返回索引
//按行,快排,这个函数对应的是按行存储的格式，目前没有使用
static void SortRows(const Eigen::MatrixXf &input, int n, int *output, int m, int row) {
    if (m > 1) {
        int i = 0;
        int j = m - 1;
        int tmp = output[i];
        while (i < j) {
            while (j > i && input(row, output[j]) > input(row, tmp))
                --j;
            if (j > i)
                output[i++] = output[j];  //只改变索引顺序
            while (j > i && input(row, i) < input(row, tmp))
                ++i;
            if (j > i)
                output[j--] = output[i];  //只改变索引顺序
        }
        output[i] = tmp;
        SortRows(input, n, output, i, row);
        SortRows(input, n, output+i+1, m-i-1, row);
    }
//    for (int j = 0; j < m; ++j) {
//        std::cout << output[j];
//    }
//    std::cout << std::endl;
}

//按行,插入排序,与存储方式无关
static void SortCols2(const Eigen::MatrixXf &input, Eigen::MatrixXi &output, int row){
//static void SortCols2(const Eigen::MatrixXf &input, int *output, int *id, int rows, int cols, int col) {
    int cols = input.cols();

    for (int i = 1; i < cols; ++i) {
        for (int j = i; j>0 && input(row, output(row, j)) < input(row, output(row, j-1)); --j) {
            int id = output(row, j);
            output(row, j) = output(row, j-1);
            output(row, j-1) = id;
        }
    }

}
//按列,选择排序,对应于存储按行,目前没有使用
//static void SortCols(const Eigen::MatrixXf &input, int *output, int rows, int cols, int col) {
//    for (int b = 0; b < rows; ++b) {
//        for (int j = 0, a = rows; j < a-b-1; ++j) {
//            if(input(col, output[j*cols]) > input(col, output[(j+1)*cols])){
////                for (int k = 0; k < cols; ++k) {
//                    int temp = output[(j+1)*cols];
//                    output[(j+1)*cols] = output[j*cols];
//                    output[j*cols] = temp;
////                }
//            }
//        }
//    }
//    for (int i = 0; i < rows; ++i) {
//        std::cout << output[i*cols];
//    }
//    std::cout<<std::endl;
//    for (int b = 0; b < arr.length; b++) {
//        for (int j = 0, a=arr.length; j < a-b-1; j++) {
//            if(arr[j][i]>arr[j+1][i]){
//                for (int k = 0; k < arr[0].length; k++) {
//                    int temp=arr[j+1][k];
//                    arr[j+1][k]=arr[j][k];
//                    arr[j][k]=temp;
//                }
//            }
//        }
//    }
//}
