//
// Created by root on 7/19/18.
//

#ifndef SONGCOMPARE_FEATURES_H
#define SONGCOMPARE_FEATURES_H

#include <vector>
#include <algorithm>
#include <eigen3/Eigen/Dense>
#include "Num.h"

#include <essentia/algorithmfactory.h>
#include <essentia/essentiamath.h> // for the isSilent function
#include <essentia/pool.h>

using namespace essentia;
using namespace standard;

//原唱与伴奏之间的差距
const float TIMES = 1.4;

//float比较相等的阈值范围
const float MIN_THR = 0.000001f;
//预设的帧范围
const int MATRIX_ROW = 1800;
const int MATRIX_COL = 1025;

const int FRAMESIZE = 2048;
const int HOPSIZE = 512;
const int SAMPLERATE = 44100;

//欧氏距离
int euclideanDistance(const std::vector<int> &s1, const std::vector<int> &s2);
float euclideanDistance(const Eigen::MatrixXf &s1, const Eigen::MatrixXf &s2);
//汉明距离
int hammingDistance(const std::vector<int> &s1, const std::vector<int> &s2);
int hammingDistance(const Eigen::MatrixXf &s1, const Eigen::MatrixXf &s2);
//编辑距离
int editDistance(const std::vector<int> &s1, const std::vector<int> &s2);
int editDistance(const Eigen::MatrixXf &s1, const Eigen::MatrixXf &s2);

//将特征进行编码
std::vector<int> featureDecoding(const std::vector<float> &input);
Eigen::MatrixXf featureDecoding(const Eigen::MatrixXf &input);

//  特征处理模块的函数
Eigen::MatrixXf original_music(std::string path1, std::string path2);

Eigen::MatrixXf features(std::string path3);

//获取stft后的矩阵
static void stft(std::string path, Eigen::MatrixXf &out);

#endif //SONGCOMPARE_FEATURES_H
