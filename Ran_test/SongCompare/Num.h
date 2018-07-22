//
// Created by root on 7/20/18.
//

#ifndef SONGCOMPARE_NUM_H
#define SONGCOMPARE_NUM_H

#include <vector>
#include <eigen3/Eigen/Dense>

//实现python中argsort函数，将矩阵按列(type=0)按行(type=1)进行排序，输出索引
Eigen::MatrixXi argsort(const Eigen::MatrixXf &input, int type);

#endif //SONGCOMPARE_NUM_H
