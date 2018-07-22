//
// Created by root on 7/19/18.
//

#ifndef SONGCOMPARE_FEATURES_H
#define SONGCOMPARE_FEATURES_H

#include <vector>
#include <algorithm>

//欧氏距离
int euclideanDistance(const std::vector<int> &s1, const std::vector<int> &s2);
//汉明距离
int hammingDistance(const std::vector<int> &s1, const std::vector<int> &s2);
//编辑距离
int editDistance(const std::vector<int> &s1, const std::vector<int> &s2);

std::vector<int> featureDecode();

#endif //SONGCOMPARE_FEATURES_H
