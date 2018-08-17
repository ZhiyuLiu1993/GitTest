//
// Created by root on 7/23/18.
//

#ifndef SONGCOMPARE_COMPARING_H
#define SONGCOMPARE_COMPARING_H

#include <eigen3/Eigen/Dense>
//#include <string>

//最终接口，两个待比较流，一个比较长度（可以改为默认值）
float simDistance(const char *org_buffer, unsigned int org_len,
                   const char *test_buffer, unsigned int test_len,
                    float cmp_length = 0.5);

Eigen::MatrixXf features(const char *ori_buffer, unsigned int ori_len, float pre, float cmp_length);

float computeDegree(Eigen::MatrixXf &feature1, Eigen::MatrixXf &feature2);

//int wav2pcm(std::string path, char **buffer, int len);

#endif //SONGCOMPARE_COMPARING_H
