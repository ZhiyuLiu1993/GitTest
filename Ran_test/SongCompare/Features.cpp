//
// Created by root on 7/19/18.
//

#include "Features.h"

int euclideanDistance(const std::vector<int> &s1, const std::vector<int> &s2){
    int distance = 0;
    int length = s1.size() > s2.size() ? s2.size() : s1.size();
    for (int i = 0; i < length; ++i) {
        if(s1[i] == s2[i])
            continue;
        else
            distance += abs(s1[i] - s2[i]);
    }
    return distance;
}

float euclideanDistance(const Eigen::MatrixXf &s1, const Eigen::MatrixXf &s2){
    float distance = 0;
    float tmp;
    int length = s1.size() > s2.size() ? s2.size() : s1.size();
    const float *data1 = s1.data();
    const float *data2 = s2.data();
    for (int i = 0; i < length; ++i) {
        if(data1[i]-data2[i]<MIN_THR && data2[i]-data1[i]<MIN_THR)
            continue;
        else {
            tmp = data1[i] - data2[i];
            if(tmp > 0)
                distance += tmp;
            else
                distance -= tmp;
        }
    }
    return distance;
}

int hammingDistance(const std::vector<int> &s1, const std::vector<int> &s2){
    int distance = 0;
    int length = s1.size() > s2.size() ? s2.size() : s1.size();
    for (int i = 0; i < length; ++i) {
        if(s1[i] != s2[i])
            distance += 1;
        else
            continue;
    }
    return distance;
}

int hammingDistance(const Eigen::MatrixXf &s1, const Eigen::MatrixXf &s2){
    int distance = 0;
    int length = s1.size() > s2.size() ? s2.size() : s1.size();
    const float *data1 = s1.data();
    const float *data2 = s2.data();
    for (int i = 0; i < length; ++i) {
        if(data1[i]-data2[i]<MIN_THR && data2[i]-data1[i]<MIN_THR)
            continue;
        else
            distance += 1;
    }
    return distance;
}

int editDistance(const std::vector<int> &s1, const std::vector<int> &s2){

    int n = s1.size();
    int m = s2.size();
    if (m == 0) return n;
    if (n == 0) return m;
    //Construct a matrix
    typedef std::vector<std::vector<int> >  Tmatrix;
    Tmatrix matrix(n + 1);
    for (int i = 0; i <= n; i++)  matrix[i].resize(m + 1);

    //step 2 Initialize

    for (int i = 1; i <= n; i++) matrix[i][0] = i;
    for (int i = 1; i <= m; i++) matrix[0][i] = i;

    //step 3
    for (int i = 1; i <= n; i++)
    {
        int si = s1[i - 1];
        //step 4
        for (int j = 1; j <= m; j++)
        {

            int sj = s2[j - 1];
            //step 5
            int cost = 0;
            if (si == sj){
                cost = 0;
            }
            else{
                cost = 1;
            }
            //step 6
            const int above = matrix[i - 1][j] + 1;
            const int left = matrix[i][j - 1] + 1;
            const int diag = matrix[i - 1][j - 1] + cost;
            matrix[i][j] = std::min(above, std::min(left, diag));

        }
    }//step7
    return matrix[n][m];

//    unsigned int s1_size = s1.size();
//    unsigned int s2_size = s2.size();
//
//    std::vector<std::vector<int>> mat(s1_size+1);
//    for (int i = 0; i < s1_size+1; ++i) {
//        mat[i].resize(s2_size+1);
//    }
//    for (int i = 1; i < s1_size+1; ++i) {
//        mat[i][0] = i;
//    }
//    for (int i = 1; i < s2_size+1; ++i) {
//        mat[0][i] = i;
//    }
//
//    int distance = 0;
//    int temp = 0;
//
//    for (int i = 1; i < s1_size+1; ++i) {
//        for (int j = 1; j < s2_size+1; ++j) {
//            if(s1[i-1] == s2[j-1])
//                distance = 0;
//            else
//                distance = 1;
//
//            temp = std::min(mat[i-1][j]+1, mat[i][j-1]+1);
//            mat[i][j] = std::min(temp, mat[i-1][j-1]+distance);
//        }
//    }
//
//    return mat[s1_size][s2_size];
}

int editDistance(const Eigen::MatrixXf &s1, const Eigen::MatrixXf &s2){
    int n = s1.size();
    int m = s2.size();
    if (m == 0) return n;
    if (n == 0) return m;
    const float *data1 = s1.data();
    const float *data2 = s2.data();
    //Construct a matrix
    typedef std::vector<std::vector<int> >  Tmatrix;
    Tmatrix matrix(n + 1);
    for (int i = 0; i <= n; i++)  matrix[i].resize(m + 1);

    //step 2 Initialize

    for (int i = 1; i <= n; i++) matrix[i][0] = i;
    for (int i = 1; i <= m; i++) matrix[0][i] = i;

    //step 3
    for (int i = 1; i <= n; i++)
    {
        float si = data1[i-1];
        //step 4
        for (int j = 1; j <= m; j++)
        {

            float sj = data2[j-1];
            //step 5
            int cost = 0;
            if (si-sj<MIN_THR && sj-si<MIN_THR){
                cost = 0;
            }
            else{
                cost = 1;
            }
            //step 6
            const int above = matrix[i - 1][j] + 1;
            const int left = matrix[i][j - 1] + 1;
            const int diag = matrix[i - 1][j - 1] + cost;
            matrix[i][j] = std::min(above, std::min(left, diag));
        }
    }//step7
    return matrix[n][m];
}

std::vector<int> featureDecoding(const std::vector<float> &input){
    std::vector<int> result;
    float base = input[0];
    result.push_back(0);
    for (int i = 1; i < input.size(); ++i) {
        if(input[i] > base){
            result.push_back(1);
        } else if(input[i] < base){
            result.push_back(-1);
        } else  if(input[i]-base<MIN_THR || base-input[i]<MIN_THR){
            result.push_back(0);
        }
        base = input[i];
    }
    return result;
}

Eigen::MatrixXf featureDecoding(const Eigen::MatrixXf &input){
    Eigen::MatrixXf result;
    result.resize(1,input.size());
    const  float *data = input.data();
    float base = data[0];
    result(0,0) = 0;
    for (int i = 1; i < input.size(); ++i) {
        if(data[i] > base){
            result(0,i) = 1;
        } else if(data[i] < base){
            result(0,i) = -1;
        } else  if(data[i]-base<MIN_THR && base-data[i]<MIN_THR){
            result(0,i) = 0;
        }
        base = data[i];
    }
    return result;
}

//TODO:与feature函数是相似的，可以考虑再进行一层封装
Eigen::MatrixXf original_music(std::string path1, std::string path2){
    //path1的矩阵
    Eigen::MatrixXf out1(MATRIX_ROW, MATRIX_COL);
    stft(path1, out1);
    //path2的矩阵
    Eigen::MatrixXf out2(MATRIX_ROW, MATRIX_COL);
    stft(path2, out2);

    Eigen::MatrixXf output = out1 - TIMES*out2;

    output = ampliTudeToDb(output);

    return output;
}

Eigen::MatrixXf features(std::string path3){
    Eigen::MatrixXf output;
    return output;
}

static void stft(std::string path, Eigen::MatrixXf &out){
    //Construct a matrix
    typedef std::vector<std::vector<float> >  Tmatrix;
    Tmatrix matrix;
    matrix.reserve(MATRIX_ROW);
    for (int i = 0; i < MATRIX_ROW; i++)  matrix[i].resize(MATRIX_COL);

    essentia::init();
//    Pool pool;
    int framesize = FRAMESIZE;
    int hopsize = HOPSIZE;
    int sr = SAMPLERATE;
    AlgorithmFactory& factory = AlgorithmFactory::instance();

    // audio loader (we always need it...)
    Algorithm* audioload = factory.create("MonoLoader",
                                          "filename", path,
                                          "sampleRate",sr,
                                          "downmix","mix");
//    cout << audioload << endl;
    std::vector<Real> audio;
    audioload->output("audio").set(audio);
    audioload->compute();

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

        if (!frame.size())
            break;

//        if (isSilent(frame))
//            continue;

        window->compute();
        spectrum->compute();
        pitchDetect->compute();
        allPitches.push_back(thisPitch);
        localTime+=float(hopsize)/float(sr);
        time.push_back(localTime);
        allConf.push_back(thisConf);

        memcpy(matrix[i].data(), spec.data(), sizeof(float));

        ++i;
    }
    // clean up
    delete frameCutter;
    delete spectrum;
    delete pitchDetect;

    out.resize(i, MATRIX_COL);
    for (int k = 0; k < i; ++k) {
        for (int j = 0; j < MATRIX_COL; ++j) {
            out(k, j) = matrix[k][j];
        }
    }
}
