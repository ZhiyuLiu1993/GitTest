//
// Created by root on 7/20/18.
//

#ifndef SONGCOMPARE_NUM_H
#define SONGCOMPARE_NUM_H

#include <vector>
#include <math.h>
#include <eigen3/Eigen/Dense>

#include <fstream>

#include <sys/time.h>

static int IF_INIT = 0;

extern Eigen::MatrixXi FFT_FRE;
//初始化频率向量，因为无法在全局进行,这个函数必须在开始时调用
void frequencyInit();

//实现python中argsort函数，将矩阵按列(type=0)按行(type=1)进行排序，输出索引
Eigen::MatrixXi argSort(const Eigen::MatrixXf &input, int type);

//获取矩阵中小于或大于某个值的索引，type = 1表示小于，0表示大于
std::vector<std::pair<int, int> > getIdx(const Eigen::MatrixXf &input, int type, int thres);

//获取矩阵中小于或大于某个值的索引，type = 1表示小于，0表示大于，并设置为target的值
void getAndSetIdx(Eigen::MatrixXf &input, int type, int thres, float target);

//将矩阵中的对应索引值设置为传入值
void setIdx(Eigen::MatrixXf &input, const std::vector<std::pair<int, int> > &idx, float target);

//
Eigen::MatrixXf ampliTudeToDb(Eigen::MatrixXf &input, float amin=1e-5, float top_db=80.0);

//获取矩阵的绝对值
Eigen::MatrixXf matrixAbs(const Eigen::MatrixXf &input);

//得到两个序列中较大值组成的序列
Eigen::MatrixXf maximum(float num, const Eigen::MatrixXf &input);

//
Eigen::MatrixXf powerToDb(const Eigen::MatrixXf &input, float ref=1e-10, float amin=1e-10, float top_db=80.0);



#endif //SONGCOMPARE_NUM_H
