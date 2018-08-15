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
    //####1
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

    //####2
//    Eigen::MatrixXf input(3, 9);
//////    Eigen::Matrix<float, 3, 4, Eigen::RowMajor> input(3, 4);
//    input << 1.1, 2.2, 0.1, 2.1, 0.00001, 0.6666, 212, 0.000007, 0.000007,
//            0.00001, 0.6666, 212, 0.00007, 1.3, 2.2, 3.1, 4.1, 0.00002,
//            4.1, 3.2, 2.1, 0.000003, 1.1, 0.0000032, 0.443545, 0.00000031, 0.00000031,
//////    Eigen::MatrixXf input(4, 3);
//////    input << 1.1, 2.2, 0.1,
//////            2.1, 1.3, 2.2,
//////            3.1, 4.1, 4.3,
//////            3.2, 2.1, 1.1;
//////            1.1, 2.2, 0.1, 2.0;
//    std::cout << input << std::endl;
//    Eigen::MatrixXi output = argsort(input, 0);
//    std::cout << output << std::endl;
//
    //####3
//    Eigen::MatrixXi output = argsort(input, 1);
////    Eigen::MatrixXi output2 = argsort(input, 0);
//    std::cout << output << std::endl;

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

    //####4
//    Eigen::MatrixXf input(3, 4);
//    input << 8.1, 5.2, 0.1, 4.1,
//            1.3, 9.2, 7.1, 4.1,
//            4.1, 13.2, -2.1, 5.1;
//    std::vector<std::pair<int, int> > res = getidx(input, 0, 5);
////    for (int i = 0; i < res.size(); ++i) {
////        std::cout << res[i].first << " " << res[i].second << std::endl;
////    }
////    std::cout << std::endl;
//
//    setidx(input, res, -100);
//    std::cout << input << std::endl;

    //####5
//    std::vector<float> input;
//    input.push_back(1.1);
//    input.push_back(1.10000001);
//    input.push_back(0.1);
//    input.push_back(0.1);
//    input.push_back(0.103);
//    input.push_back(0.103);
//    input.push_back(10.103);
//
//    std::vector<int> res = featureDecoding(input);
//    for (int i = 0; i < res.size(); ++i) {
//        std::cout << res[i] << " ";
//    }
//    std::cout << std::endl;

    //####6
//    Eigen::MatrixXf input(3, 4);
//    input << 8.1, 5.2, 0.1, 4.1,
//            1.3, 9.2, 7.1, 4.1,
//            4.1, 13.2, -2.1, 5.1;
//    Eigen::MatrixXf res(3, 4);
//    Eigen::MatrixXf tmp;
//    for (int i = 0; i < input.rows(); ++i) {
//        tmp = featureDecoding(input.row(i));
////        std::cout << tmp <<std::endl;
//        for (int j = 0; j < tmp.size(); ++j) {
//            res(i, j) = tmp(0, j);
//        }
////        res.row(i) = featureDecoding(input.row(i));
////        tmp = input.row(i);
////        float *data = tmp.data();
////        std::cout << tmp.size() << std::endl;
////        for (int j = 0; j < tmp.size(); ++j) {
////            std::cout << data[j] << std::endl;
////        }
////        std::cout << std::endl;
//    }
//    std::cout << res <<std::endl;

    //####7
//    Eigen::MatrixXf input(3, 5);
//    input << 1, 0, 0, -1, 1,
//            1, 0, 0, -1, 1,
//            4.1, 13.2, -2.1, 5.1, 6;
//    Eigen::MatrixXf output = matrixAbs(input);
//    std::cout << output << std::endl;
//    Eigen::MatrixXf input2(1, 8);
//    input2 << 1, 1, 1, 1, 1, 3, 4, 5;
//    std::cout << hammingDistance(input.row(0), input.row(1)) << std::endl;
//    std::cout << editDistance(input.row(0), input.row(1)) << std::endl;
//    std::cout << euclideanDistance(input.row(0), input.row(1)) << std::endl;

    ////FINAL TEST
    //####8
//    string path1, path2, path3;
//    sim_distance(path1, path2, path3);
//
//
//     register the algorithms in the factory(ies
#if 0
//    essentia::init();
//    Pool pool;

    /////// PARAMS //////////////
    int framesize = 2048;
    int hopsize = 512;
    int sr = 44100;
    std::string audioFilename = "./song/pcm/1530243263.pcm";
    FILE *f;
    f = fopen(audioFilename.c_str(), "rb");
    if(f == NULL)
        return -1;
    fseek(f, 0, SEEK_END);
    unsigned int len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = (char *)malloc(len);
    len = fread(buffer, 1, len, f);
    fclose(f);


    // register the algorithms in the factory(ies)
    essentia::init();
    AlgorithmFactory& factory = AlgorithmFactory::instance();

    // audio loader (we always need it...)
    Algorithm* audioload = factory.create("MonoLoader",
//                                          "filename", audioFilename,
                                          "sampleRate",sr,
                                          "downmix","mix");
//    cout << audioload << endl;
    std::vector<Real> audio;
    for (int j = 0; j < len; ++j) {
        audio.push_back(*buffer++);
    }
//    audioload->output("audio").set(audio);
//    audioload->compute();
    std::cout << "monophonic pitch estimation Yin FFT" << std::endl;

    // create algorithms
    Algorithm* frameCutter = factory.create("FrameCutter",
                                            "frameSize", framesize,
                                            "hopSize", hopsize,
                                            "startFromZero", false);

    Algorithm* window = factory.create("Windowing",
                                       "type", "hann",
                                       "size",framesize,
                                       "zeroPadding", 0);

    Algorithm* spectrum = factory.create("Spectrum",
                                         "size", framesize);

    Algorithm* pitchDetect = factory.create("PitchYinFFT",
                                            "frameSize", framesize,
                                            "sampleRate", sr);


    // configure frameCutter:
    std::vector<Real> frame;
    frameCutter->input("signal").set(audio);
    frameCutter->output("frame").set(frame);

    // configure windowing:
    std::vector<Real> windowedframe;
    window->input("frame").set(frame);
    window->output("frame").set(windowedframe);

    // configure spectrum:
    std::vector<Real> spec;
    spectrum->input("frame").set(windowedframe);
    spectrum->output("spectrum").set(spec);

    // configure pitch extraction:
    Real thisPitch = 0., thisConf = 0;
    Real localTime=0.;
    std::vector<Real> allPitches, allConf, time;
    pitchDetect->input("spectrum").set(spec);
    pitchDetect->output("pitch").set(thisPitch);
    pitchDetect->output("pitchConfidence").set(thisConf);


    // process:
    int i = 0;
    while (true) {
        frameCutter->compute();
//        cout << frameCutter << endl;

        if (!frame.size())
            break;
//
//        if (isSilent(frame))
//            continue;

        window->compute();
        spectrum->compute();
        pitchDetect->compute();
        allPitches.push_back(thisPitch);
        localTime+=float(hopsize)/float(sr);
        time.push_back(localTime);
        allConf.push_back(thisConf);
//        cout << spec.size() << ":" << spec << endl;
        i += 1;
        std::cout << i << ":" << spec << std::endl;
//        std::cout << i << ":" << frame << std::endl;



    }

    // write to csv file
//    ofstream outfile(argv[2]);
//    std::cout << "time   pitch [Hz]  pitch confidence" << std::endl;
//    cout << spec[0] << endl;

//    for (int i=0; i<(int)time.size(); i++){
//        cout << spec << endl;
////        cout << time[i] << ", " << allPitches[i] << ", " << allConf[i] << "," << spec[i] << endl;
//        cout << time[i] << ", " << spec << endl;
//    }
//    outfile.close();

    // clean up
    delete frameCutter;
    delete spectrum;
    delete pitchDetect;
#endif

    //####9
//    Eigen::MatrixXf input(5, 5);
//    input << 1, 0, 0, -1, 1,
//            1, 0, 0, -1, 1,
//            4.1, 13.2, -2.1, 5.1, 6,
//            4.1, 13.2, -2.1, 5.1, 6,
//            4.1, 13.2, -2.1, 5.1, 6;
//
////    input = input * 10;
//    input = input * input;
//    std::cout << input << std::endl;

    //####10
//    Eigen::MatrixXf input1(1025, 980);
//    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> input1;
//    input1.resize(4, 4);
//    std::ifstream indata;
//
//    indata.open("./song/front.csv");
//
//    std::string                line;
//    while (getline(indata, line))
//    {
//        std::stringstream          lineStream(line);
//        std::string                cell;
//
//        while (std::getline(lineStream, cell, ','))
//        {
//            std::cout << cell << std::endl;
//            //Process cell
//        }
//    }
//    Eigen::MatrixXf input1(3, 4);
//    input1 <<
//            4,5,6,5,
//            1,2,3,4,
//            4,6,7,8;
//    std::cout << input1*TIMES << std::endl;
//    input1 = ampliTudeToDb(input1);
//    std::cout << input1 << std::endl;
//    input1 = input1.block(0,0,4,3);
//    input1 = input1.block<3,4>(0, 0);
//    std::cout << input1 << std::endl;
//    Eigen::MatrixXf input = ampliTudeToDb(input1);
//    std::cout << input << std::endl;

//    frequencyInit();
//    std::cout << FFT_FRE << std::endl;
    //####11
//    typedef std::vector<std::vector<float> >  Tmatrix;
//    Tmatrix matrix;
//    matrix.reserve(MATRIX_ROW);
//    for (int i = 0; i < MATRIX_ROW; i++)  matrix[i].reserve(MATRIX_COL);
//    std::cout << matrix.size() << std::endl;
//    float *data = matrix[0].data();
//    std::vector<float> temp(10, 10);
//    memcpy(data, temp.data(), sizeof(float)*10);
//
//    for (int j = 0; j < 10; ++j) {
//        std::cout << matrix[0][j] << ' ';
//    }

    //####12
//    Eigen::MatrixXf input1(4, 4);
//    input1.resize(3, 4);
//    input1 << 0.079,0.894,1.164,0.432,
//            1.994,1.834,0.764,0.276,
//            3.488,7.303,8.798,9.142;
//    std::cout << input1 << std::endl;
//    std::cout << std::endl;
////    input1.transposeInPlace();
//    Eigen::MatrixXf out = input1.transpose();
//    std::cout << out << std::endl;

    //####MOST
//    std::string path1 = "./song/z.wav";
//    std::string path2 = "./song/2.wav";
//    std::string path3 = "./song/1530242944.wav";
//    std::string path4= "./song/1530243052.wav";
//    std::string path5 = "./song/1530243158.wav";
//    std::string path6 = "./song/1530243258.wav";
//    std::string path7 = "./song/1530243263.wav";
//    std::string path8 = "./song/1530243284.wav";
//    std::string path1 = "./song/pcm/.pcm";
//    std::string path2 = "./song/pcm/2.pcm";
    std::string path0 = "./song/pcm/1530242944.pcm";
    std::string path1 = "./song/pcm/1530243052.pcm";
    std::string path2 = "./song/pcm/1530243158.pcm";
    std::string path3 = "./song/pcm/1530243258.pcm";
    std::string path4 = "./song/pcm/1530243263.pcm";
    std::string path5 = "./song/pcm/1530243284.pcm";
//    std::string path9 = "./song/pcm/1530243436.pcm";
//    struct timeval tv;
//    struct timeval tv2;
//    gettimeofday(&tv, NULL);
    clock_t startTime, endTime;
    std::vector<std::string> path;
    path.clear();
//    path.push_back(path1);
//    path.push_back(path2);
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

//    int i = atoi(argv[1]);
//    int j = atoi(argv[2]);
//    float ratio = atof(argv[3]);
//    std::cout << "i:" << i << " j:" << j << " ratio:" << ratio << endl;

//    readFile(path[i], &buf1, len1);
//    readFile(path[j], &buf2, len2);
    readFile(path0, &buf1, len1);
    readFile(path1, &buf2, len2);

//    for (int i = 0; i < path.size()-1; ++i) {
//    for (int i = 0; i < path.size()-1; ++i) {
//        for (int j = i+1; j < path.size(); ++j) {
    startTime = clock();
//            std::cout << "pi:" << path[i] << "  pj:" << path[j] << endl;
//            std::cout << sim_distance(path4, path3) << std::endl;
//    std::cout << sim_distance(buf1, len1, buf2, len2, ratio) << std::endl;
    std::cout << sim_distance(buf1, len1, buf2, len2, 0.5) << std::endl;
//        std::cout << sim_distance(path9, path9, path[i]) << std::endl;
    endTime = clock();
    std::cout << "Total Time: " << (double)(endTime - startTime) /CLOCKS_PER_SEC<< "s" << std::endl;;
    std::cout << "-----------------------------------------------------------" << endl;

    return 0;
}