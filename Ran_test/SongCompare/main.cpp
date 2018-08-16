#include <iostream>

#include "Features.h"
#include "Num.h"
#include "Comparing.h"

#include <cstdio>
#include <cstdlib>

#include <sys/time.h>
#include <samplerate.h>


//#define TEST_FINAL 0

//void set(int *a){
//    a[0] = 100;
//}
//extern Eigen::MatrixXi FFT_FRE;
using namespace std;

static void readFile(std::string path, char **buffer, unsigned int &buf_len){
    FILE *f;
    f = fopen(path.c_str(), "rb");
    if(f == NULL)
        return;
    fseek(f, 0, SEEK_END);
    unsigned int len = ftell(f);
    fseek(f, 0, SEEK_SET);
    //FIXME::这块考虑是否可以使用静态的
    *buffer = (char *)malloc(len);

    len = fread(*buffer, 1, len, f);
    fclose(f);

    buf_len = len;
}

int main(int argc, char *argv[]) {

    std::string path0 = "./song/pcm/1530242944.pcm";
    std::string path1 = "./song/pcm/1530243052.pcm";
    std::string path2 = "./song/pcm/1530243158.pcm";
    std::string path3 = "./song/pcm/1530243258.pcm";
    std::string path4 = "./song/pcm/1530243263.pcm";
    std::string path5 = "./song/pcm/1530243284.pcm";

    clock_t startTime, endTime;
    clock_t startAllTime, endAllTime;
    std::vector<std::string> path;
    path.clear();
    path.push_back(path0);
    path.push_back(path1);
    path.push_back(path2);
    path.push_back(path3);
    path.push_back(path4);
    path.push_back(path5);
//    path.push_back(path9);

    char *buf1;
    unsigned int len1;
    char *buf2;
    unsigned int len2;

//    if(argc != 4){
//        cout << "param num error!" << endl;
//        return -1;
//    }
//
//    int i = atoi(argv[1]);
//    int j = atoi(argv[2]);
//    float ratio = atof(argv[3]);
//    std::cout << "i:" << i << " j:" << j << " ratio:" << ratio << endl;
//
//    readFile(path[i], &buf1, len1);
//    readFile(path[j], &buf2, len2);
    readFile(path0, &buf1, len1);
    readFile(path4, &buf2, len2);

//    startTime = clock();
//    std::cout << sim_distance(buf1, len1, buf2, len2, ratio) << std::endl;
//    std::cout << sim_distance(buf1, len1, buf2, len2, 0.5) << std::endl;
//    endTime = clock();
//    std::cout << "Total Time: " << (double)(endTime - startTime) /CLOCKS_PER_SEC<< "s" << std::endl;;
//    std::cout << "-----------------------------------------------------------" << endl;

    startAllTime = clock();
    startTime = clock();
    Eigen::MatrixXf tmp1 = features(buf1, len1, 2.75, 0.5);
    endTime = clock();
    std::cout << "Feature1 Time: " << (double)(endTime - startTime) /CLOCKS_PER_SEC<< "s" << std::endl;;
    startTime = clock();
    Eigen::MatrixXf tmp2 = features(buf2, len2, 2.75, 0.5);
    endTime = clock();
    std::cout << "Feature2 Time: " << (double)(endTime - startTime) /CLOCKS_PER_SEC<< "s" << std::endl;;
    startTime = clock();
    std::cout << computeDegree(tmp1, tmp2) << endl;
    endTime = clock();
    std::cout << "compute Time: " << (double)(endTime - startTime) /CLOCKS_PER_SEC<< "s" << std::endl;;
    std::cout << "-----------------------------------------------------------" << endl;
    endAllTime = clock();
    std::cout << "compute Time: " << (double)(endAllTime - startAllTime) /CLOCKS_PER_SEC<< "s" << std::endl;;
    return 0;
}