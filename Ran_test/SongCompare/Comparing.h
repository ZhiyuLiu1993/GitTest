//
// Created by root on 7/23/18.
//

#ifndef SONGCOMPARE_COMPARING_H
#define SONGCOMPARE_COMPARING_H

#include <eigen3/Eigen/Dense>
#include "Features.h"
#include "Num.h"

float sim_distance(std::string path1, std::string path2, std::string path3);
////这个函数在另一个文件中定义
//Eigen::MatrixXf feature_decoding(Eigen::MatrixXf s);
float sim_distance(std::string path1, std::string path2);

double degree(double a);

#endif //SONGCOMPARE_COMPARING_H
