//
// Created by root on 7/20/18.
//

#include "Num.h"

#include <iostream>

static void SortRows(const Eigen::MatrixXf &input, int n, int *output, int m, int row);
static void SortRows2(const Eigen::MatrixXf &input, int n, int *output, int m, int row);
//static void SortCols(const Eigen::MatrixXf &input, int *output, int rows, int cols, int col);
static void SortCols2(const Eigen::MatrixXf &input, Eigen::MatrixXi &output, int row);
static void SortRowsMerge(const Eigen::MatrixXf &input, int *output, int *temp,
                          int first, int last, int rows);

Eigen::MatrixXi FFT_FRE(1, 1025);

Eigen::MatrixXi argsort(const Eigen::MatrixXf &input, int type){
    int rows = input.rows();
    int cols = input.cols();
    Eigen::MatrixXi output(rows, cols);
//    Eigen::Matrix<int, rows, cols, Eigen::RowMajor> output(3, 4);
    if(!type){   //按列
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                output(i, j) = i;
//                std::cout <<  *(output.data()+k);
//                *(output.data()+i*cols+j) = i;
            }
        }
//        for (int k = 0; k < output.size(); ++k) {
//            std::cout <<  *(output.data()+k);
//        }
//        std::cout << std::endl;
//        std::cout << output << std::endl;
        int *temp = new int[rows+1];
        for (int i = 0; i < cols; ++i) {
//            int *id = output.data();
//            Sort(input, cols, id, cols, i);
//            SortCols(input, output.data()+i, rows, cols, i);
//            SortRows2(input, rows, output.data()+i*rows, rows, i);
            SortRowsMerge(input, output.data()+i*rows, temp, 0, rows-1, i);
        }
        delete []temp;

    } else{      //按行
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                output(i, j) = j;
            }
        }

//        for (int k = 0; k < output.size(); ++k) {
//            std::cout <<  *(output.data()+k);
//        }
//        std::cout << std::endl;

//        std::cout << output << std::endl;
        for (int i = 0; i < rows; ++i) {
//            int *id = output.data();
//            Sort(input, cols, id, cols, i);
//            for (int j = 0; j < cols; ++j) {
//                std::cout <<  *(output.data()+i*cols+j);
//            }
//            std::cout << std::endl;

//            int *id = output.data();
            SortCols2(input, output, i);
//            SortRows(input, cols, id+i*cols, cols, i);
        }
    }
//    std::cout << output << std::endl;
//    int *data = output.data();
//    for (int i = 0; i < output.size(); ++i) {
//        std::cout << data[i];
//    }
//    std::cout<<std::endl;
    return output;
}

void SortOr(int a[], int n, int id[], int m) {
    if (m > 1) {
        int i = 0;
        int j = m - 1;
        int tmp = id[i];
        while (i < j) {
            while (j > i && a[id[j]] > a[tmp])
                --j;
            if (j > i)
                id[i++] = id[j];  //只改变索引顺序
            while (j > i && a[id[i]] < a[tmp])
                ++i;
            if (j > i)
                id[j--] = id[i];  //只改变索引顺序
        }
        id[i] = tmp;
        SortOr(a, n, id, i);
        SortOr(a, n, id + i + 1, m - i - 1);
    }
}

static void merge(const Eigen::MatrixXf &input, int first, int mid,
                  int last, int *output, int *temp, int rows){
    int i = first;
    int j = mid+1;
    int m = mid;
    int n = last;
    int k = 0;

    while (i <= m && j <= n){
        if(input(output[i], rows) <= input(output[j], rows))
            temp[k++] = output[i++];
        else
            temp[k++] = output[j++];
    }
    while(i <= m)
        temp[k++] = output[i++];
    while(j <= n)
        temp[k++] = output[j++];
    for (int i = 0; i < k; ++i) {
        output[first+i] = temp[i];
    }

}

//merge sort
//TODO:考虑不传整个矩阵只传部分
static void SortRowsMerge(const Eigen::MatrixXf &input, int *output, int *temp,
                          int first, int last, int rows) {
    if(first < last){
        int mid = (first + last) / 2;
        SortRowsMerge(input, output, temp, first, mid, rows);
        SortRowsMerge(input, output, temp, mid+1, last, rows);
        merge(input, first, mid, last, output, temp, rows);
    }
}

//FIXME::n是多余的
//因为Matrix的矩阵数据是按列存储的,所以在排序计算索引时时使用不同的算法，按列时使用递归的快排
static void SortRows2(const Eigen::MatrixXf &input, int n, int *output, int m, int row) {
    if (m > 1) {
        int i = 0;
        int j = m - 1;
        int tmp = output[i];
        while (i < j) {
            while (j > i && input(output[j], row) > input(tmp, row))
                --j;
            if (j > i)
                output[i++] = output[j];  //只改变索引顺序
            while (j > i && input(i, row) < input(tmp, row))
                ++i;
            if (j > i)
                output[j--] = output[i];  //只改变索引顺序
        }
        output[i] = tmp;
        SortRows2(input, n, output, i, row);
        SortRows2(input, n, output+i+1, m-i-1, row);
    }
//    for (int j = 0; j < m; ++j) {
//        std::cout << output[j];
//    }
//    std::cout << std::endl;
}
//实现两种类型sort,返回索引
//按行,快排,这个函数对应的是按行存储的格式，目前没有使用
static void SortRows(const Eigen::MatrixXf &input, int n, int *output, int m, int row) {
    if (m > 1) {
        int i = 0;
        int j = m - 1;
        int tmp = output[i];
        while (i < j) {
            while (j > i && input(row, output[j]) > input(row, tmp))
                --j;
            if (j > i)
                output[i++] = output[j];  //只改变索引顺序
            while (j > i && input(row, i) < input(row, tmp))
                ++i;
            if (j > i)
                output[j--] = output[i];  //只改变索引顺序
        }
        output[i] = tmp;
        SortRows(input, n, output, i, row);
        SortRows(input, n, output+i+1, m-i-1, row);
    }
//    for (int j = 0; j < m; ++j) {
//        std::cout << output[j];
//    }
//    std::cout << std::endl;
}

//按行,插入排序,与存储方式无关
static void SortCols2(const Eigen::MatrixXf &input, Eigen::MatrixXi &output, int row){
//static void SortCols2(const Eigen::MatrixXf &input, int *output, int *id, int rows, int cols, int col) {
    int cols = input.cols();

    for (int i = 1; i < cols; ++i) {
        for (int j = i; j>0 && input(row, output(row, j)) < input(row, output(row, j-1)); --j) {
            int id = output(row, j);
            output(row, j) = output(row, j-1);
            output(row, j-1) = id;
        }
    }

}
//按列,选择排序,对应于存储按行,目前没有使用
//static void SortCols(const Eigen::MatrixXf &input, int *output, int rows, int cols, int col) {
//    for (int b = 0; b < rows; ++b) {
//        for (int j = 0, a = rows; j < a-b-1; ++j) {
//            if(input(col, output[j*cols]) > input(col, output[(j+1)*cols])){
////                for (int k = 0; k < cols; ++k) {
//                    int temp = output[(j+1)*cols];
//                    output[(j+1)*cols] = output[j*cols];
//                    output[j*cols] = temp;
////                }
//            }
//        }
//    }
//    for (int i = 0; i < rows; ++i) {
//        std::cout << output[i*cols];
//    }
//    std::cout<<std::endl;
//    for (int b = 0; b < arr.length; b++) {
//        for (int j = 0, a=arr.length; j < a-b-1; j++) {
//            if(arr[j][i]>arr[j+1][i]){
//                for (int k = 0; k < arr[0].length; k++) {
//                    int temp=arr[j+1][k];
//                    arr[j+1][k]=arr[j][k];
//                    arr[j][k]=temp;
//                }
//            }
//        }
//    }
//}

std::vector<std::pair<int, int> > getidx(const Eigen::MatrixXf &input, int type, int thres){
    int rows = input.rows();
    int cols = input.cols();
    std::vector<std::pair<int, int> > result;
    if(type){
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if(input(i,j) <= thres){
                    result.push_back(std::make_pair(i, j));
                }
            }
        }
    } else{
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if(input(i,j) >= thres){
                    result.push_back(std::make_pair(i, j));
                }
            }
        }
    }
    return result;
}

void setidx(Eigen::MatrixXf &input, const std::vector<std::pair<int, int> > &idx, float target){
    for (int i = 0; i < idx.size(); ++i) {
        input(idx[i].first, idx[i].second) = target;
    }
}

Eigen::MatrixXf matrixAbs(const Eigen::MatrixXf &input){
    const float *data = input.data();
    Eigen::MatrixXf output(input.rows(), input.cols());
    float *out = output.data();
    for (int i = 0; i < input.size(); ++i) {
        if(data[i] < 0)
            out[i] = -data[i];
        else
            out[i] = data[i];
    }
    return output;
}

Eigen::MatrixXf ampliTudeToDb(Eigen::MatrixXf &input, float amin, float top_db){
    Eigen::MatrixXf magnitude = matrixAbs(input);

    float *data = magnitude.data();
    float max = data[0];
    data[0] *= data[0];
    for (int i = 1; i < magnitude.size(); ++i) {
        if(data[i] > max)
            max = data[i];   //先求最大值再对矩阵值进行计算
        data[i] *= data[i]; //这里表示了python中的square函数，而不是两个矩阵相乘，这个矩阵行列是完全不同的
    }

    return powerToDb(magnitude, max*max, amin*amin, top_db);
}

Eigen::MatrixXf powerToDb(const Eigen::MatrixXf &input, float ref, float amin, float top_db){
    float ref_value = ref;
    if(ref_value < 0)
        ref_value = -ref_value;

    Eigen::MatrixXf log_spec = maximum(amin, input);

    int length = log_spec.size();
    float *data = log_spec.data();
    for (int i = 0; i < length; ++i) {
        data[i] = log(data[i]) / log(10) * 10;
    }
//    log_spec = log_spec * 10;
    float num = amin;
    if(amin < ref_value)
        num = ref_value;
    num = 10 * (log(num) / log(10));

    data[0] -= num;
    float max = data[0];
    for (int i = 1; i < length; ++i) {
        data[i] -= num;             //此处是求完值以后才计算最大值
        if(data[i] > max)
            max = data[i];
    }

    log_spec = maximum(max-top_db, log_spec);

    return log_spec;

}

//TODO:此处可以考虑修改传进去的矩阵,而不是返回临时变量产生拷贝开销
Eigen::MatrixXf maximum(const float num, const Eigen::MatrixXf &input){
    int length = input.size();
    int rows = input.rows();
    int cols = input.cols();
    Eigen::MatrixXf output(rows, cols);
    const float *in_data = input.data();
    float *out_data = output.data();
    for (int i = 0; i < length; ++i) {
        if(num > in_data[i])
            out_data[i] = num;
        else
            out_data[i] = in_data[i];
    }
    return output;
}

void frequencyInit(){
    FFT_FRE << 0,21,43,64,86,107,129,150,172,193,215,236,258,279,301,322,344,366,387,409,430,452,473,495,516,538,559,581,
            602,624,645,667,689,710,732,753,775,796,818,839,861,882,904,925,947,968,990,1012,1033,1055,1076,1098,1119,1141,
            1162,1184,1205,1227,1248,1270,1291,1313,1335,1356,1378,1399,1421,1442,1464,1485,1507,1528,1550,1571,1593,1614,
            1636,1658,1679,1701,1722,1744,1765,1787,1808,1830,1851,1873,1894,1916,1937,1959,1981,2002,2024,2045,2067,2088,
            2110,2131,2153,2174,2196,2217,2239,2260,2282,2304,2325,2347,2368,2390,2411,2433,2454,2476,2497,2519,2540,2562,
            2583,2605,2627,2648,2670,2691,2713,2734,2756,2777,2799,2820,2842,2863,2885,2906,2928,2950,2971,2993,3014,3036,
            3057,3079,3100,3122,3143,3165,3186,3208,3229,3251,3273,3294,3316,3337,3359,3380,3402,3423,3445,3466,3488,3509,
            3531,3552,3574,3596,3617,3639,3660,3682,3703,3725,3746,3768,3789,3811,3832,3854,3875,3897,3919,3940,3962,3983,
            4005,4026,4048,4069,4091,4112,4134,4155,4177,4198,4220,4242,4263,4285,4306,4328,4349,4371,4392,4414,4435,4457,
            4478,4500,4521,4543,4565,4586,4608,4629,4651,4672,4694,4715,4737,4758,4780,4801,4823,4844,4866,4888,4909,4931,
            4952,4974,4995,5017,5038,5060,5081,5103,5124,5146,5167,5189,5211,5232,5254,5275,5297,5318,5340,5361,5383,5404,
            5426,5447,5469,5490,5512,5534,5555,5577,5598,5620,5641,5663,5684,5706,5727,5749,5770,5792,5813,5835,5857,5878,
            5900,5921,5943,5964,5986,6007,6029,6050,6072,6093,6115,6136,6158,6180,6201,6223,6244,6266,6287,6309,6330,6352,
            6373,6395,6416,6438,6459,6481,6503,6524,6546,6567,6589,6610,6632,6653,6675,6696,6718,6739,6761,6782,6804,6826,
            6847,6869,6890,6912,6933,6955,6976,6998,7019,7041,7062,7084,7105,7127,7149,7170,7192,7213,7235,7256,7278,7299,
            7321,7342,7364,7385,7407,7428,7450,7472,7493,7515,7536,7558,7579,7601,7622,7644,7665,7687,7708,7730,7751,7773,
            7795,7816,7838,7859,7881,7902,7924,7945,7967,7988,8010,8031,8053,8074,8096,8118,8139,8161,8182,8204,8225,8247,
            8268,8290,8311,8333,8354,8376,8397,8419,8441,8462,8484,8505,8527,8548,8570,8591,8613,8634,8656,8677,8699,8720,
            8742,8764,8785,8807,8828,8850,8871,8893,8914,8936,8957,8979,9000,9022,9043,9065,9087,9108,9130,9151,9173,9194,
            9216,9237,9259,9280,9302,9323,9345,9366,9388,9410,9431,9453,9474,9496,9517,9539,9560,9582,9603,9625,9646,9668,
            9689,9711,9733,9754,9776,9797,9819,9840,9862,9883,9905,9926,9948,9969,9991,10012,10034,10056,10077,10099,10120,
            10142,10163,10185,10206,10228,10249,10271,10292,10314,10335,10357,10379,10400,10422,10443,10465,10486,10508,
            10529,10551,10572,10594,10615,10637,10658,10680,10702,10723,10745,10766,10788,10809,10831,10852,10874,10895,
            10917,10938,10960,10981,11003,11025,11046,11068,11089,11111,11132,11154,11175,11197,11218,11240,11261,11283,
            11304,11326,11347,11369,11391,11412,11434,11455,11477,11498,11520,11541,11563,11584,11606,11627,11649,11670,
            11692,11714,11735,11757,11778,11800,11821,11843,11864,11886,11907,11929,11950,11972,11993,12015,12037,12058,
            12080,12101,12123,12144,12166,12187,12209,12230,12252,12273,12295,12316,12338,12360,12381,12403,12424,12446,
            12467,12489,12510,12532,12553,12575,12596,12618,12639,12661,12683,12704,12726,12747,12769,12790,12812,12833,
            12855,12876,12898,12919,12941,12962,12984,13006,13027,13049,13070,13092,13113,13135,13156,13178,13199,13221,
            13242,13264,13285,13307,13329,13350,13372,13393,13415,13436,13458,13479,13501,13522,13544,13565,13587,13608,
            13630,13652,13673,13695,13716,13738,13759,13781,13802,13824,13845,13867,13888,13910,13931,13953,13975,13996,
            14018,14039,14061,14082,14104,14125,14147,14168,14190,14211,14233,14254,14276,14298,14319,14341,14362,14384,
            14405,14427,14448,14470,14491,14513,14534,14556,14577,14599,14621,14642,14664,14685,14707,14728,14750,14771,
            14793,14814,14836,14857,14879,14900,14922,14944,14965,14987,15008,15030,15051,15073,15094,15116,15137,15159,
            15180,15202,15223,15245,15267,15288,15310,15331,15353,15374,15396,15417,15439,15460,15482,15503,15525,15546,
            15568,15590,15611,15633,15654,15676,15697,15719,15740,15762,15783,15805,15826,15848,15869,15891,15913,15934,
            15956,15977,15999,16020,16042,16063,16085,16106,16128,16149,16171,16192,16214,16236,16257,16279,16300,16322,
            16343,16365,16386,16408,16429,16451,16472,16494,16515,16537,16559,16580,16602,16623,16645,16666,16688,16709,
            16731,16752,16774,16795,16817,16838,16860,16882,16903,16925,16946,16968,16989,17011,17032,17054,17075,17097,
            17118,17140,17161,17183,17205,17226,17248,17269,17291,17312,17334,17355,17377,17398,17420,17441,17463,17484,
            17506,17528,17549,17571,17592,17614,17635,17657,17678,17700,17721,17743,17764,17786,17807,17829,17851,17872,
            17894,17915,17937,17958,17980,18001,18023,18044,18066,18087,18109,18130,18152,18174,18195,18217,18238,18260,
            18281,18303,18324,18346,18367,18389,18410,18432,18453,18475,18497,18518,18540,18561,18583,18604,18626,18647,
            18669,18690,18712,18733,18755,18776,18798,18820,18841,18863,18884,18906,18927,18949,18970,18992,19013,19035,
            19056,19078,19099,19121,19143,19164,19186,19207,19229,19250,19272,19293,19315,19336,19358,19379,19401,19422,
            19444,19466,19487,19509,19530,19552,19573,19595,19616,19638,19659,19681,19702,19724,19745,19767,19789,19810,
            19832,19853,19875,19896,19918,19939,19961,19982,20004,20025,20047,20068,20090,20112,20133,20155,20176,20198,
            20219,20241,20262,20284,20305,20327,20348,20370,20391,20413,20435,20456,20478,20499,20521,20542,20564,20585,
            20607,20628,20650,20671,20693,20714,20736,20758,20779,20801,20822,20844,20865,20887,20908,20930,20951,20973,
            20994,21016,21037,21059,21081,21102,21124,21145,21167,21188,21210,21231,21253,21274,21296,21317,21339,21360,
            21382,21404,21425,21447,21468,21490,21511,21533,21554,21576,21597,21619,21640,21662,21683,21705,21727,21748,
            21770,21791,21813,21834,21856,21877,21899,21920,21942,21963,21985,22006,22028,22050;
    IF_INIT = 1;
}
