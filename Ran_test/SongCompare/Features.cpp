//
// Created by root on 7/19/18.
//

#include <iomanip>
#include <samplerate.h>
#include "Features.h"

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

        }
    }//step7
    return matrix[n][m];
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

//FIXME:目前的可能存在内存泄露问题，buffer在不同地方申请与释放
Eigen::MatrixXf original_music_buffer(std::string path1, std::string path2){
    if(!IF_INIT)
        frequencyInit();
    //path1的矩阵
    Eigen::MatrixXf out1(MATRIX_ROW, MATRIX_COL);

    std::vector<Real> audio;
    readFile(path1, audio);
    stft(audio, out1);


    //path2的矩阵
//    Eigen::MatrixXf out2(MATRIX_ROW, MATRIX_COL);
    Eigen::MatrixXf out2;
    readFile(path2, audio);
    stft(audio, out2);


    //TODO:考虑少用几个复制的矩阵
    Eigen::MatrixXf output = out1 - TIMES*out2;

    output = ampliTudeToDb(output);

    std::vector<std::pair<int, int> > idx = getidx(output, SMALL, MIN_ORI_DB);
    setidx(output, idx, SET_MIN_DB);

    //FIXME::#########################################
//    Eigen::MatrixXi mat_index = argsort(output, 1);
#if 1
    output.transposeInPlace();
    Eigen::MatrixXi mat_index = argsort(output, 0);
//    mat_index.transposeInPlace();
#endif
//    mat_index.transposeInPlace();


    int cur_col = mat_index.cols();
//    std::cout << mat_index.rows() << "   " << mat_index.cols() << std::endl;
//    std::cout << MATRIX_COL-MATRIX_RANGE << std::endl;
    Eigen::MatrixXf result(MATRIX_RANGE, cur_col);
//    std::cout << result.rows() << "   " << result.cols() << std::endl;
    int index;
    for (int i = MATRIX_COL-MATRIX_RANGE; i < MATRIX_COL; ++i) {
        for (int j = 0; j < cur_col; ++j) {
            //从FFT_FRE中获取对应排序索引的频率,目前取最大的6列，即最后6列
//            std::cout << " i: "  << i << "  j: " << j << std::endl;
            index = mat_index(i, j);
//            std::cout << " index: "  << index << std::endl;
            result(i-(MATRIX_COL-MATRIX_RANGE), j) = FFT_FRE(0, index);
//            std::cout << "result:  " << result(i, j) << std::endl;
        }
    }

//    std::cout << result.rows() << "   " << result.cols() << std::endl;
    idx = getidx(result, GREATE, MAX_DB);
    setidx(result, idx, 0);

    return result;
}
//TODO:与feature函数是相似的，可以考虑再进行一层封装
Eigen::MatrixXf original_music(std::string path1, std::string path2){
    if(!IF_INIT)
        frequencyInit();
    //path1的矩阵
    Eigen::MatrixXf out1(MATRIX_ROW, MATRIX_COL);
    stft(path1, out1);

    //path2的矩阵
//    Eigen::MatrixXf out2(MATRIX_ROW, MATRIX_COL);
    Eigen::MatrixXf out2;
    stft(path2, out2);
//    assert(out1.rows()==out2.rows() && out1.cols()==out2.cols());

    //TODO:考虑少用几个复制的矩阵
    Eigen::MatrixXf output = out1 - TIMES*out2;

    output = ampliTudeToDb(output);


    std::vector<std::pair<int, int> > idx = getidx(output, SMALL, MIN_ORI_DB);
    setidx(output, idx, SET_MIN_DB);

    //FIXME::#########################################
//    Eigen::MatrixXi mat_index = argsort(output, 1);
#if 1
    output.transposeInPlace();
    Eigen::MatrixXi mat_index = argsort(output, 0);
//    mat_index.transposeInPlace();
#endif
//    mat_index.transposeInPlace();


    int cur_col = mat_index.cols();
//    std::cout << mat_index.rows() << "   " << mat_index.cols() << std::endl;
//    std::cout << MATRIX_COL-MATRIX_RANGE << std::endl;
    Eigen::MatrixXf result(MATRIX_RANGE, cur_col);
//    std::cout << result.rows() << "   " << result.cols() << std::endl;
    int index;
    for (int i = MATRIX_COL-MATRIX_RANGE; i < MATRIX_COL; ++i) {
        for (int j = 0; j < cur_col; ++j) {
            //从FFT_FRE中获取对应排序索引的频率,目前取最大的6列，即最后6列
//            std::cout << " i: "  << i << "  j: " << j << std::endl;
            index = mat_index(i, j);
//            std::cout << " index: "  << index << std::endl;
            result(i-(MATRIX_COL-MATRIX_RANGE), j) = FFT_FRE(0, index);
//            std::cout << "result:  " << result(i, j) << std::endl;
        }
    }

//    std::cout << result.rows() << "   " << result.cols() << std::endl;
    idx = getidx(result, GREATE, MAX_DB);
    setidx(result, idx, 0);

    return result;
}

Eigen::MatrixXf features_buffer(std::string path3){
    if(!IF_INIT)
        frequencyInit();
    Eigen::MatrixXf output;
    std::vector<Real> audio;
    readFile(path3, audio);
    stft(audio, output);
//    stft(path3, output);
    output = ampliTudeToDb(output);
//    std::cout << output.rows() << "   " << output.cols() << std::endl;

    std::vector<std::pair<int, int> > idx = getidx(output, SMALL, MIN_HUMAN_DB);
    setidx(output, idx, SET_MIN_DB);

//    Eigen::MatrixXi mat_index = argsort(output, 1);
//    mat_index.transposeInPlace();
#if 1
    output.transposeInPlace();
    Eigen::MatrixXi mat_index = argsort(output, 0);
//    mat_index.transposeInPlace();
#endif

    int cur_col = mat_index.cols();
//    std::cout << mat_index.rows() << "   " << mat_index.cols() << std::endl;
//    std::cout << MATRIX_COL-MATRIX_RANGE << std::endl;
    Eigen::MatrixXf result(MATRIX_RANGE, cur_col);
    int index;
    for (int i = MATRIX_COL-MATRIX_RANGE; i < MATRIX_COL; ++i) {
        for (int j = 0; j < cur_col; ++j) {
            //从FFT_FRE中获取对应排序索引的频率,目前取最大的6列，即最后6列
            index = mat_index(i, j);
            result(i-(MATRIX_COL-MATRIX_RANGE), j) = FFT_FRE(0, index);
        }
    }

    idx = getidx(result, GREATE, MAX_DB);
    setidx(result, idx, 0);


    return result;
}

Eigen::MatrixXf features(std::string path3){
    if(!IF_INIT)
        frequencyInit();
    Eigen::MatrixXf output;
    stft(path3, output);
    output = ampliTudeToDb(output);
//    std::cout << output.rows() << "   " << output.cols() << std::endl;

    std::vector<std::pair<int, int> > idx = getidx(output, SMALL, MIN_HUMAN_DB);
    setidx(output, idx, SET_MIN_DB);

//    Eigen::MatrixXi mat_index = argsort(output, 1);
//    mat_index.transposeInPlace();
#if 1
    output.transposeInPlace();
    Eigen::MatrixXi mat_index = argsort(output, 0);
//    mat_index.transposeInPlace();
#endif

    int cur_col = mat_index.cols();
//    std::cout << mat_index.rows() << "   " << mat_index.cols() << std::endl;
//    std::cout << MATRIX_COL-MATRIX_RANGE << std::endl;
    Eigen::MatrixXf result(MATRIX_RANGE, cur_col);
    int index;
    for (int i = MATRIX_COL-MATRIX_RANGE; i < MATRIX_COL; ++i) {
        for (int j = 0; j < cur_col; ++j) {
            //从FFT_FRE中获取对应排序索引的频率,目前取最大的6列，即最后6列
            index = mat_index(i, j);
            result(i-(MATRIX_COL-MATRIX_RANGE), j) = FFT_FRE(0, index);
        }
    }

    idx = getidx(result, GREATE, MAX_DB);
    setidx(result, idx, 0);


    return result;
}

static void stft(std::vector<Real> &audio, Eigen::MatrixXf &out){
    if(!IF_INIT)
        frequencyInit();
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
                                          "sampleRate",sr,
                                          "downmix","mix");
//    cout << audioload << endl;
//    std::vector<Real> audio;
//    for (int j = 0; j < len; ++j) {
//        audio.push_back(*buffer++);
//    }
//    free(buffer);
//    buffer = NULL;
//    audioload->output("audio").set(audio);
//    audioload->compute();

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

//    for (int l = 0; l < audio.size(); ++l) {
//        std::cout << audio[l] << std::endl;
//    }
//    std::cout << audio.size() << std::endl;
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
//    Real thisPitch = 0., thisConf = 0;
//    Real localTime=0.;
//    std::vector<Real> allPitches, allConf, time;
//    pitchDetect->input("spectrum").set(spec);
//    pitchDetect->output("pitch").set(thisPitch);
//    pitchDetect->output("pitchConfidence").set(thisConf);

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
//        pitchDetect->compute();
//        allPitches.push_back(thisPitch);
//        localTime+=float(hopsize)/float(sr);
//        time.push_back(localTime);
//        allConf.push_back(thisConf);

        for (int j = 0; j < spec.size(); ++j) {
            matrix[i][j] = spec[j];
        }

//        memcpy(matrix[i].data(), spec.data(), sizeof(float)*spec.size());

        ++i;
    }
//    std::cout << spec.size() << std::endl;
//    std::cout << i << std::endl;
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
                                          "sampleRate",sr);
//                                          "sampleRate",sr,
//                                          "downmix","mix");
//    cout << audioload << endl;
    std::vector<Real> audio;
    audioload->output("audio").set(audio);
    audioload->compute();

//    for (int l = 0; l < audio.size(); ++l) {
//        std::cout << audio[l] << std::endl;
//    }
//    std::cout << audio.size() << std::endl;


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
//    Real thisPitch = 0., thisConf = 0;
//    Real localTime=0.;
//    std::vector<Real> allPitches, allConf, time;
//    pitchDetect->input("spectrum").set(spec);
//    pitchDetect->output("pitch").set(thisPitch);
//    pitchDetect->output("pitchConfidence").set(thisConf);

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
//        pitchDetect->compute();
//        allPitches.push_back(thisPitch);
//        localTime+=float(hopsize)/float(sr);
//        time.push_back(localTime);
//        allConf.push_back(thisConf);

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

//FIXME::此处buffer类型还需要验证
static void readFile(std::string path, std::vector<Real> &audio){
    audio.clear();

    FILE *f;
    f = fopen(path.c_str(), "rb");
    if(f == NULL)
        return;
    fseek(f, 0, SEEK_END);
    unsigned int len = ftell(f);
    fseek(f, 0, SEEK_SET);
    //FIXME::这块考虑是否可以使用静态的
    char *buffer = (char *)malloc(len);
    len = fread(buffer, 1, len, f);
//    std::cout << len << std::endl;
    fclose(f);

    int input_len = len;
    float *in = (float *)malloc(input_len*sizeof(float));
    SRC_DATA data;
    float *out = (float *)malloc(input_len*3*sizeof(float));
    data.src_ratio = SAMPLERATE / ORRSAMPLE;
    for (int j = 0; j < len/2; ++j) {
        char bl = buffer[2*j];
        char bh = buffer[2*j+1];

        short s = (short)((bh & 0x00FF) << 8 | bl & 0x00FF);
        float ft = s / 32768.0;
        in[j] = ft;
//        std::cout << f << std::endl;
    }
    data.input_frames = input_len;
    data.output_frames = input_len*3;
    data.data_in = in;
    data.data_out = out;
    int error;
    if(error = src_simple(&data, SRC_SINC_FASTEST, 1)){
        std::cout << src_strerror(error) << std::endl;
    }

    for (int i = 0; i < data.output_frames_gen; ++i) {
        audio.push_back(out[i]);
    }
    free(buffer);
    free(in);
    free(out);
}

void bufferToFloat(const char *buffer, unsigned int len, std::vector<Real> &audio){
    audio.clear();

    //使用静态分配的内存，看是否比动态分配的速度快
    static float in[MAXBUFFLEN];
    static float out[RATIOSIZE*MAXBUFFLEN];
    memset(in, 0, sizeof(float)*MAXBUFFLEN);
    memset(out, 0, sizeof(float)*MAXBUFFLEN*RATIOSIZE);
    SRC_DATA data;
    data.src_ratio = SAMPLERATE / ORRSAMPLE;
    for (int j = 0; j < len/2; ++j) {
        char bl = buffer[2*j];
        char bh = buffer[2*j+1];

        short s = (short)((bh & 0x00FF) << 8 | bl & 0x00FF);
        float ft = s / 32768.0;
        in[j] = ft;
//        std::cout << f << std::endl;
    }
    data.input_frames = MAXBUFFLEN;
    data.output_frames = MAXBUFFLEN*RATIOSIZE;
    data.data_in = in;
    data.data_out = out;
    int error;
    if(error = src_simple(&data, SRC_SINC_FASTEST, 1)){
        std::cout << src_strerror(error) << std::endl;
    }

    for (int i = 0; i < data.output_frames_gen; ++i) {
        audio.push_back(out[i]);
    }
}

Eigen::MatrixXf features_buffer(const char *org_buffer, unsigned int org_len, float cmp_length){
    if(!IF_INIT)
        frequencyInit();

    Eigen::MatrixXf output;
    std::vector<Real> audio;

    bufferToFloat(org_buffer, org_len*cmp_length, audio);

    stft(audio, output);
//    stft(path3, output);
    output = ampliTudeToDb(output);
//    std::cout << output.rows() << "   " << output.cols() << std::endl;

    std::vector<std::pair<int, int> > idx = getidx(output, SMALL, MIN_HUMAN_DB);
    setidx(output, idx, SET_MIN_DB);

//    Eigen::MatrixXi mat_index = argsort(output, 1);
//    mat_index.transposeInPlace();
#if 1
    output.transposeInPlace();
    Eigen::MatrixXi mat_index = argsort(output, 0);
//    mat_index.transposeInPlace();
#endif

    int cur_col = mat_index.cols();
//    std::cout << mat_index.rows() << "   " << mat_index.cols() << std::endl;
//    std::cout << MATRIX_COL-MATRIX_RANGE << std::endl;
    Eigen::MatrixXf result(MATRIX_RANGE, cur_col);
    int index;
    for (int i = MATRIX_COL-MATRIX_RANGE; i < MATRIX_COL; ++i) {
        for (int j = 0; j < cur_col; ++j) {
            //从FFT_FRE中获取对应排序索引的频率,目前取最大的6列，即最后6列
            index = mat_index(i, j);
            result(i-(MATRIX_COL-MATRIX_RANGE), j) = FFT_FRE(0, index);
        }
    }

    idx = getidx(result, GREATE, MAX_DB);
    setidx(result, idx, 0);


    return result;
}
