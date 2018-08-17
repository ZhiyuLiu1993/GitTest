//
// Created by root on 7/23/18.
//

#include <iomanip>
#include "Comparing.h"
#include "Features.h"
#include "Num.h"

//static clock_t startTime, endTime;
static double degree(double a);

float computeDegree(Eigen::MatrixXf &feature1, Eigen::MatrixXf &feature2){
    //  定义编码序列
    Eigen::MatrixXi f1(feature1.rows(), feature1.cols());
    Eigen::MatrixXi f2(feature2.rows(), feature2.cols());

    //  对特征序列进行编码
    Eigen::MatrixXi tmp;
    for (int i=0;i<feature1.rows();i++){
        tmp = featureDecoding(feature1.row(i));
        for (int j = 0; j < tmp.size(); ++j) {
            f1(i, j) = tmp(0, j);
        }
    }
    for (int i=0;i<feature2.rows();i++){
        tmp = featureDecoding(feature2.row(i));
        for (int j = 0; j < tmp.size(); ++j) {
            f2(i, j) = tmp(0, j);
        }
    }

    //  定义距离结果
    double res1[6], res2[6], res3[6];
    //  定义距离之和
    double d1=0, d2=0, d3=0;

    // 求编码长度
    double length = std::min(f1.cols(), f2.cols()) - START_INDEX;

    //  计算欧式距离,编辑距离,汉明距离
    for (int i=5;i>=0;i--){
        //  归一化距离的度量
        res1[i] = euclideanDistance(f1.row(i), f2.row(i)) / (length * 2);
        res2[i] = editDistance(f1.row(i), f2.row(i)) / length;
        res3[i] = hammingDistance(f1.row(i), f2.row(i)) / length;
//        std::cout << euclideanDistance(f1.row(i), f2.row(i)) / (length*2) << " ";
//        std::cout << editDistance(f1.row(i), f2.row(i)) / length << " ";
//        std::cout << hammingDistance(f1.row(i), f2.row(i)) / length << std::endl;

        d1 += res1[i];
        d2 += res2[i];
        d3 += res3[i];
    }

    // 均值
    double res1_mean = d1 / 6;
    double res2_mean = d2 / 6;
    double res3_mean = d3 / 6;
    //相似度
    double d = degree(res2[0]);
//    std::cout << d << " " << res2[0] << "   " << res2[1] << "   "<< res2[2] << "   "<<
//              res2[3] << "   "<<  res2[4] << "   "<<  res2[5] << "   "<<std::endl;

//    if (res2_mean < 0.35 && res3[5] <= 0.31){
//        d = 0.7 * d + 0.3;
//    }
//    else if (res2_mean <= 0.40 && res3[5] <= 0.41){
//        d = 0.5 * d + 0.2 + 0.3 * ((0.40 - res2_mean) / 0.05);
//    }
//    else{
//        d = 0.7 * d;
//    }
    //编辑距离对结果的影响
    if (0 < res2_mean && res2_mean <= 0.25){
        d = 0.5 * d + 0.4 + 0.1 * ((0.25 - res2_mean) / 0.25);
    } else if (0.25 < res2_mean && res2_mean <= 0.30){
        d = 0.5 * d + 0.4 + 0.1 * ((0.30 - res2_mean) / 0.05);
    } else if(0.30 < res2_mean && res2_mean <= 0.35){
        d = 0.6 * d + 0.3 + 0.1 * ((0.35 - res2_mean) / 0.05);
    } else if(0.35 < res2_mean && res2_mean <= 1){
        d = 0.9 * d;
    }
    //汉明距离对结果的影响
    if(0 < res3_mean && res3_mean <= 0.30){
        d = d * 0.7 + 0.3;
    }else if(0.30 < res3_mean && res3_mean <= 0.45){
        d = d * 0.9 + 0.1;
    }else if(0.45 < res3_mean && res3_mean <= 1){
        d = d * 0.8;
    }

    //欧氏距离对结果的影响
    if(res1_mean > 0.25){
        d = d * 0.7;
    }

    return d;
}

//  相似度计算仿射函数，解决if嵌套
static double degree(double a){
    if (0.0 <= a && a <= 0.10) return 0.95 + ((0.1 - a) / 2);
    if (0.10 < a && a <= 0.15) return 0.90 + (0.05 * (0.15 - a) / 0.05);
    if (0.15 < a && a <= 0.20) return 0.85 + (0.05 * (0.20 - a) / 0.05);
    if (0.20 < a && a <= 0.25) return 0.75 + (0.10 * (0.25 - a) / 0.05);
    if (0.25 < a && a <= 0.30) return 0.60 + (0.15 * (0.30 - a) / 0.05);
    if (0.30 < a && a <= 0.35) return 0.45 + (0.15 * (0.35 - a) / 0.05);
    if (0.35 < a && a <= 0.40) return 0.30 + (0.15 * (0.40 - a) / 0.05);
    if (0.40 < a && a <= 0.45) return 0.20 + (0.10 * (0.45 - a) / 0.05);
    if (0.45 < a && a <= 1.0) return (0.20 * (1.0 - a) / 0.55);
}

float simDistance(const char *org_buffer, unsigned int org_len,
                   const char *test_buffer, unsigned int test_len,
                   float cmp_length){
//    startTime = clock();
    Eigen::MatrixXf feature1 = featuresBuffer(org_buffer, org_len, cmp_length);
//    endTime = clock();
//    std::cout << "feature_buffer Time: " << (double)(endTime - startTime) /CLOCKS_PER_SEC<< "s" << std::endl;;
    Eigen::MatrixXf feature2 = featuresBuffer(test_buffer, test_len, cmp_length);

    return computeDegree(feature1, feature2);
}

Eigen::MatrixXf features(const char *ori_buffer, unsigned int ori_len, float pre, float cmp_length){
    return featuresBuffer(ori_buffer, ori_len, pre, cmp_length);
}
