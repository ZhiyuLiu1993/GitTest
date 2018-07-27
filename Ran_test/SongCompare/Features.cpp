//
// Created by root on 7/19/18.
//

#include <iomanip>
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

float euclideanDistance(const Eigen::MatrixXi &s1, const Eigen::MatrixXi &s2){
    int distance = 0;
    int tmp;
    int length = s1.size() > s2.size() ? s2.size() : s1.size();
    const int *data1 = s1.data();
    const int *data2 = s2.data();
    for (int i = START_INDEX; i < length; ++i) {
        if(data1[i] == data2[i])
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

int hammingDistance(const Eigen::MatrixXi &s1, const Eigen::MatrixXi &s2){
    int distance = 0;
    int length = s1.size() > s2.size() ? s2.size() : s1.size();
    const int *data1 = s1.data();
    const int *data2 = s2.data();
    for (int i = START_INDEX; i < length; ++i) {
        if(data1[i] == data2[i])
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

int editDistance(const Eigen::MatrixXi &s1, const Eigen::MatrixXi &s2){
    int n = s1.size();
    int m = s2.size();
    if (m == 0) return n;
    if (n == 0) return m;
    const int *data1 = s1.data() + START_INDEX;
    const int *data2 = s2.data() + START_INDEX; //此处从START_INDEX处开始，这个矩阵是一维的，即使按列存储也是可以的
    //Construct a matrix

    //从START_INDEX处开始计算
    n -= START_INDEX;
    m -= START_INDEX;

    typedef std::vector<std::vector<int> >  Tmatrix;
    Tmatrix matrix(n + 1);
    for (int i = 0; i <= n; i++)  matrix[i].resize(m + 1);

    //step 2 Initialize

    for (int i = 0; i <= n; i++) matrix[i][0] = i;
    for (int i = 0; i <= m; i++) matrix[0][i] = i;

    //step 3
    for (int i = 1; i <= n; i++)
    {
//        float si = data1[i-1];
        //step 4
        for (int j = 1; j <= m; j++)
        {
            if(data1[i-1] == data2[j-1])
                matrix[i][j] = matrix[i-1][j-1];
            else{
                int nm =  std::min(matrix[i-1][j], matrix[i][j-1]);
                matrix[i][j] = 1 + std::min(matrix[i-1][j-1], nm);
            }

//            float sj = data2[j-1];
//            //step 5
//            int cost = 0;
//            if (si-sj<MIN_THR && sj-si<MIN_THR){
//                cost = 0;
//            }
//            else{
//                cost = 1;
//            }
//            //step 6
//            const int above = matrix[i - 1][j] + 1;
//            const int left = matrix[i][j - 1] + 1;
//            const int diag = matrix[i - 1][j - 1] + cost;
//            matrix[i][j] = std::min(above, std::min(left, diag));
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

Eigen::MatrixXi featureDecoding(const Eigen::MatrixXf &input){
    Eigen::MatrixXi result;
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

#if 0
    {
        std::fstream fout;
        fout.open("./result/stft_out1.txt", std::ios::out);
        fout.setf(std::ios::left);
//        fout.width(20);
        fout.setf(std::ios::left);
        for (int k = 0; k < out1.rows(); ++k) {
            for (int i = 0; i < out1.cols(); ++i) {
                fout << out1(k, i) << " ";
            }
            fout << std::endl;
        }
        fout.close();
    };
#endif


//    std::cout << "rows: " << out1.rows() << "cols: " << out1.cols() << std::endl;
//    std::cout << "*************1end***************" << std::endl;
    //path2的矩阵
    Eigen::MatrixXf out2(MATRIX_ROW, MATRIX_COL);
    stft(path2, out2);
//    std::cout << "************2end****************" << std::endl;
//    assert(out1.rows()==out2.rows() && out1.cols()==out2.cols());
#if 0
    {
        std::fstream fout("./result/stft_out2.txt", std::ios::out);
//        fout.width(20);
        fout.setf(std::ios::left);
        for (int k = 0; k < out2.rows(); ++k) {
            for (int i = 0; i < out2.cols(); ++i) {
                fout << out2(k, i) << " ";
            }
            fout << std::endl;
        }
        fout.close();
    };
#endif

    //TODO:考虑少用几个复制的矩阵
    Eigen::MatrixXf output = out1 - TIMES*out2;
#if FILE
    {
        std::fstream fout("./result/stft_1.txt", std::ios::out);
//        fout.width(20);
        fout.setf(std::ios::left);
        for (int k = 0; k < output.rows(); ++k) {
            for (int i = 0; i < output.cols(); ++i) {
                fout << std::setw(15) << output(k, i) << " ";
            }
            fout << std::endl;
        }
        fout.close();
    };
#endif

//    std::cout << "rows: " << output.rows() << "cols: " << output.cols() << std::endl;
//    sleep(10);
//    std::cout << output << std::endl;
    output = ampliTudeToDb(output);

#if 0
    {
        std::ifstream fi("./result/ampltitude.csv");
        std::string                line;
        int i = 0;
        int j = 0;
        while (getline(fi, line))
        {
            std::stringstream          lineStream(line);
            std::string                cell;
            j = 0;
            while (std::getline(lineStream, cell, ' '))
            {
                output(i, j++) = atoi(cell.c_str());
//                std::cout << cell << " ";
            }
//            std::cout << std::endl;
            ++i;
        }
    }
#endif
#if FILE
    {
        std::fstream fout("./result/amlit_out.txt", std::ios::out);
//        fout.setf(std::ios::left);
        for (int k = 0; k < output.rows(); ++k) {
            for (int i = 0; i < output.cols(); ++i) {
//                fout << std::setw(10) << output(k, i) << " ";
                fout << output(k, i) << ",";
            }
            fout << std::endl;
        }
        fout.close();
    };
#endif
//    std::cout << output << std::endl;

    std::vector<std::pair<int, int> > idx = getidx(output, SMALL, MIN_ORI_DB);
    setidx(output, idx, SET_MIN_DB);

    //FIXME::#########################################
//    Eigen::MatrixXi mat_index = argsort(output, 1);
#if 1
    output.transposeInPlace();
    Eigen::MatrixXi mat_index = argsort(output, 0);
    mat_index.transposeInPlace();
#endif
//    mat_index.transposeInPlace();
#if FILE
    {
        std::fstream fout("./result/mat_index.txt", std::ios::out);
        fout.setf(std::ios::left);
        for (int k = 0; k < mat_index.rows(); ++k) {
            for (int i = 0; i < mat_index.cols(); ++i) {
                fout << std::setw(6) << mat_index(k, i) << " ";
            }
            fout << std::endl;
        }
        fout.close();
    };
#endif

    frequencyInit();  //FIXME::这个函数可以在最开始时调用

    int cur_row = mat_index.rows();
    Eigen::MatrixXf result(cur_row, MATRIX_RANGE);
    int index;
    for (int i = 0; i < cur_row; ++i) {
        for (int j = MATRIX_RANGE; j > 0; --j) {
            //从FFT_FRE中获取对应排序索引的频率,目前取最大的6列，即最后6列
            index = mat_index(i, MATRIX_COL-j);
            result(i, MATRIX_RANGE-j) = FFT_FRE(0, index);
        }
    }

    idx = getidx(result, GREATE, MAX_DB);
    setidx(result, idx, 0);
#if FILE
    {
        std::fstream fout("./result/feature.txt", std::ios::out);
        fout.setf(std::ios::left);
        for (int k = 0; k < result.rows(); ++k) {
            for (int i = 0; i < result.cols(); ++i) {
                fout << std::setw(8) << result(k, i) << " ";
            }
            fout << std::endl;
        }
        fout.close();
    };
#endif

    return result.transpose();
}

Eigen::MatrixXf features(std::string path3){
    Eigen::MatrixXf output;
    stft(path3, output);
    output = ampliTudeToDb(output);
    std::vector<std::pair<int, int> > idx = getidx(output, SMALL, MIN_HUMAN_DB);
    setidx(output, idx, SET_MIN_DB);

//    Eigen::MatrixXi mat_index = argsort(output, 1);
//    mat_index.transposeInPlace();
#if 1
    output.transposeInPlace();
    Eigen::MatrixXi mat_index = argsort(output, 0);
    mat_index.transposeInPlace();
#endif

//    frequencyInit();  //FIXME::这个函数可以在最开始时调用

    int cur_row = mat_index.rows();
    Eigen::MatrixXf result(cur_row, MATRIX_RANGE);
    int index;
    for (int i = 0; i < cur_row; ++i) {
        for (int j = MATRIX_RANGE; j > 0; --j) {
            //从FFT_FRE中获取对应排序索引的频率,目前取最大的6列，即最后6列
            index = mat_index(i, MATRIX_COL-j);
            result(i, MATRIX_RANGE-j) = FFT_FRE(0, index);
        }
    }

    idx = getidx(result, GREATE, MAX_DB);
    setidx(result, idx, 0);

    return result.transpose();
}

static void stft(std::string path, Eigen::MatrixXf &out){
    //Construct a matrix
    typedef std::vector<std::vector<float> >  Tmatrix;
    Tmatrix matrix;
    matrix.resize(MATRIX_ROW);
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
//    std::cout << " 222" << std::endl;
    while (true) {
        frameCutter->compute();

        if (!frame.size())
            break;

        if (isSilent(frame))
            continue;

        window->compute();
        spectrum->compute();
        pitchDetect->compute();
        allPitches.push_back(thisPitch);
        localTime+=float(hopsize)/float(sr);
        time.push_back(localTime);
        allConf.push_back(thisConf);

        for (int j = 0; j < spec.size(); ++j) {
            matrix[i][j] = spec[j];
        }

//        memcpy(matrix[i].data(), spec.data(), sizeof(float)*spec.size());

        ++i;
    }
//    std::cout << " 111" << std::endl;
    // clean up
    delete frameCutter;
    delete spectrum;
    delete pitchDetect;

    out.resize(i, MATRIX_COL);
    for (int k = 0; k < i; ++k) {
        for (int j = 0; j < MATRIX_COL; ++j) {
            out(k, j) = matrix[k][j];

//            if(k == 0)
//                std::cout << out(k, j) << std::endl;
        }
    }
}
