#include <iostream>

#include "Features.h"
#include "Num.h"

//void set(int *a){
//    a[0] = 100;
//}

int main() {
//    s1.push_back(3);
//    s1.push_back(4);
//    s1.push_back(5);
//    std::vector<int> s2;
//    s2.push_back(1);
//    s2.push_back(0);
//    s2.push_back(0);
//    s2.push_back(-1);
//    s2.push_back(1);
//
//    std::cout << editDistance(s1, s2) << std::endl;
//    std::cout << hammingDistance(s1, s2) << std::endl;
//    std::cout << euclideanDistance(s1, s2) << std::endl;

    Eigen::MatrixXf input(3, 4);
//    Eigen::Matrix<float, 3, 4, Eigen::RowMajor> input(3, 4);
    input << 1.1, 2.2, 0.1, 2.1,
            1.3, 2.2, 3.1, 4.1,
            4.1, 3.2, 2.1, 1.1;
//    Eigen::MatrixXf input(4, 3);
//    input << 1.1, 2.2, 0.1,
//            2.1, 1.3, 2.2,
//            3.1, 4.1, 4.3,
//            3.2, 2.1, 1.1;
//            1.1, 2.2, 0.1, 2.0;
    std::cout << input << std::endl;

    Eigen::MatrixXi output = argsort(input, 1);
//    Eigen::MatrixXi output2 = argsort(input, 0);
    std::cout << output << std::endl;

//    Eigen::MatrixXi input(3, 4);
//    input << 1, 2, 0, 2,
//            1, 2, 3, 4,
//            4, 3, 2, 1;
//    int *data = input.data();
//    std::cout << input << std::endl;
//
//    set(data+1);
////    data[1] = 100;
//    std::cout << input << std::endl;

    return 0;
}