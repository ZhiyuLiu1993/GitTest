//
// Created by root on 7/23/18.
//

#ifndef SONGCOMPARE_COMPARING_H
#define SONGCOMPARE_COMPARING_H

#include <eigen3/Eigen/Dense>
#include "Features.h"
#include "Num.h"

float sim_distance(std::string path1, std::string path2, std::string path3);

float sim_distance(std::string path1, std::string path2);

//最终接口，两个待比较流，一个比较长度（可以改为默认值）
float sim_distance(const char *org_buffer, unsigned int org_len,
                   const char *test_buffer, unsigned int test_len,
                    float cmp_length = 0.5);

double degree(double a);

#endif //SONGCOMPARE_COMPARING_H
