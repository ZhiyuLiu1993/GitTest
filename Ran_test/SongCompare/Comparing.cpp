//
// Created by root on 7/23/18.
//

#include <iomanip>
#include "Comparing.h"

// 计算原唱，伴奏，用户歌声的相似度
float sim_distance(std::string path1, std::string path2, std::string path3) {

    // 获得原唱特征序列，伴奏特征序列
//    clock_t startTime, endTime;
//    startTime = clock();
    Eigen::MatrixXf feature1 = original_music(path1, path2);
//    endTime = clock();
//    std::cout << "original Time : " << (double)(endTime - startTime) /CLOCKS_PER_SEC<< "s" << std::endl;;
    Eigen::MatrixXf feature2 = features(path3);

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
#if FILE
    {
        std::fstream fout;
        fout.setf(std::ios::left);
        fout.open("./result/feature_code1.txt", std::ios::out);
        for (int k = 0; k < f1.rows(); ++k) {
            for (int i = 0; i < f1.cols(); ++i) {
                fout << std::setw(3) << f1(k, i) << " ";
            }
            fout << std::endl;
            for (int i = 0; i < f2.cols(); ++i) {
                fout << std::setw(3) << f2(k, i) << " ";
            }
            fout << std::endl;
        }
        fout.close();
    };
#endif
#if 0
    {
        std::fstream fout;
        fout.open("./result/feature_code2.txt", std::ios::out);
        for (int k = 0; k < f2.rows(); ++k) {
            for (int i = 0; i < f2.cols(); ++i) {
                fout << f2(k, i) << ",";
            }
            fout << std::endl;
        }
        fout.close();
    };
#endif
    //  定义距离结果
    float res1[6], res2[6], res3[6];
    //  定义距离之和
    float d1=0, d2=0, d3=0;

    // 求编码长度
    float length = std::min(f1.cols(), f2.cols()) - START_INDEX;

    //  计算欧式距离,编辑距离,汉明距离
    for (int i=5;i>=0;i--){
        //  归一化距离的度量
        res1[i] = euclideanDistance(f1.row(i), f2.row(i)) / length;
        res2[i] = editDistance(f1.row(i), f2.row(i)) / (length * 2);
        res3[i] = hammingDistance(f1.row(i), f2.row(i)) / length;
//        std::cout << editDistance(f1.row(i), f2.row(i)) << std::endl;
//        std::cout << euclideanDistance(f1.row(i), f2.row(i)) << std::endl;
//        std::cout << hammingDistance(f1.row(i), f2.row(i)) << std::endl;

        d1 += res1[i];
        d2 += res2[i];
        d3 += res3[i];
    }

    // 均值
    // float res1_mean = d1 / 6;
    float res2_mean = d2 / 6;
    // float res3_mean = d3 / 6;
    //相似度
    float d = degree(res2[5]);

    if (res2_mean < 0.35 && res3[5] <= 0.31){
        d = 0.7 * d + 0.3;
    }
    else if (res2_mean <= 0.40 && res3[5] <= 0.41){
        d = 0.5 * d + 0.2 + 0.3 * ((0.40 - res2_mean) / 0.05);
    }
    else{
        d = 0.7 * d;
    }
    return d;
}


//  相似度计算仿射函数，解决if嵌套
float degree(float a){
//    if (0 <= a <= 0.10) return 0.95 + (0.05 * (0.10 - a));
//    if (0.10 < a <= 0.15) return 0.90 + (0.05 * (0.15 - a));
//    if (0.15 < a <= 0.20) return 0.85 + (0.05 * (0.20 - a));
//    if (0.20 < a <= 0.25) return 0.75 + (0.10 * (0.25 - a));
//    if (0.25 < a <= 0.30) return 0.60 + (0.15 * (0.30 - a));
//    if (0.30 < a <= 0.35) return 0.45 + (0.15 * (0.35 - a));
//    if (0.35 < a <= 0.40) return 0.30 + (0.15 * (0.40 - a));
//    if (0.40 < a <= 0.45) return 0.20 + (0.10 * (0.45 - a));
//    if (0.45 < a <= 1.0) return (0.20 * (a - 0.45));
//    std::cout << "!!!!!!!!!!!!!" << a << std::endl;
    if (0 <= a <= 0.10) return 0.95 + (0.05 * (0.10 - a) / 0.1);
    if (0.10 < a <= 0.15) return 0.90 + (0.05 * (0.15 - a) / 0.05);
    if (0.15 < a <= 0.20) return 0.85 + (0.05 * (0.20 - a) / 0.05);
    if (0.20 < a <= 0.25) return 0.75 + (0.10 * (0.25 - a) / 0.05);
    if (0.25 < a <= 0.30) return 0.60 + (0.15 * (0.30 - a) / 0.05);
    if (0.30 < a <= 0.35) return 0.45 + (0.15 * (0.35 - a) / 0.05);
    if (0.35 < a <= 0.40) return 0.30 + (0.15 * (0.40 - a) / 0.05);
    if (0.40 < a <= 0.45) return 0.20 + (0.10 * (0.45 - a) / 0.05);
    if (0.45 < a <= 1.0) return (0.20 * (1.0 - a) / 0.55);

}