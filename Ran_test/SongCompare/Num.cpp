//
// Created by root on 7/20/18.
//

#include "Num.h"
#include <iostream>

static clock_t startTime, endTime;

//对行排序，按行存储，使用快速排序
static void sortRowsQuick(const Eigen::MatrixXf &input, int n, int *output, int m, int row);
//对列排序，按列存储，使用快速排序
static void sortColsQuick(const Eigen::MatrixXf &input, int n, int *output, int m, int row);
//对行排序，与存储方式无关(插入排序)
static void sortRowsInsert(const Eigen::MatrixXf &input, Eigen::MatrixXi &output, int row);
//对列排序，按列存储，使用归并排序
static void sortColsMerge(const Eigen::MatrixXf &input, int *output, int *temp,
                          int first, int last, int rows);
//对列排序，与存储方式无关(插入排序)
static void sortColsInsert(const Eigen::MatrixXf &input, Eigen::MatrixXi &output);

Eigen::MatrixXi FFT_FRE(1, 1025);

Eigen::MatrixXi argSort(const Eigen::MatrixXf &input, int type){
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
        startTime = clock();
        int *temp = new int[rows+1];
        for (int i = 0; i < cols; ++i) {
//            int *id = output.data();
//            Sort(input, cols, id, cols, i);
//            SortCols(input, output.data()+i, rows, cols, i);
//            sortColsQuick(input, rows, output.data()+i*rows, rows, i);
            sortColsMerge(input, output.data()+i*rows, temp, 0, rows-1, i);
//            sortColsInsert(input, output);
        }
        delete []temp;
        endTime = clock();
        std::cout << "sort Time: " << (double)(endTime - startTime) /CLOCKS_PER_SEC<< "s" << std::endl;;

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
            sortRowsInsert(input, output, i);
//            sortRowsQuick(input, cols, id+i*cols, cols, i);
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
static void sortColsMerge(const Eigen::MatrixXf &input, int *output, int *temp,
                          int first, int last, int rows) {
    if(first < last){
        int mid = (first + last) / 2;
        sortColsMerge(input, output, temp, first, mid, rows);
        sortColsMerge(input, output, temp, mid+1, last, rows);
        merge(input, first, mid, last, output, temp, rows);
    }
}

//FIXME::n是多余的
//因为Matrix的矩阵数据是按列存储的,所以在排序计算索引时使用不同的算法，按列时使用递归的快排
static void sortColsQuick(const Eigen::MatrixXf &input, int n, int *output, int m, int row) {
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
        sortColsQuick(input, n, output, i, row);
        sortColsQuick(input, n, output+i+1, m-i-1, row);
    }
//    for (int j = 0; j < m; ++j) {
//        std::cout << output[j];
//    }
//    std::cout << std::endl;
}
//实现两种类型sort,返回索引
//按行,快排,这个函数对应的是按行存储的格式，目前没有使用
static void sortRowsQuick(const Eigen::MatrixXf &input, int n, int *output, int m, int row) {
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
        sortRowsQuick(input, n, output, i, row);
        sortRowsQuick(input, n, output+i+1, m-i-1, row);
    }
//    for (int j = 0; j < m; ++j) {
//        std::cout << output[j];
//    }
//    std::cout << std::endl;
}
//按行,插入排序,与存储方式无关
static void sortRowsInsert(const Eigen::MatrixXf &input, Eigen::MatrixXi &output, int row){
    int cols = input.cols();

    for (int i = 1; i < cols; ++i) {
        for (int j = i; j>0 && input(row, output(row, j)) < input(row, output(row, j-1)); --j) {
            int id = output(row, j);
            output(row, j) = output(row, j-1);
            output(row, j-1) = id;
        }
    }

}
//按列,插入排序,与存储方式无关
static void sortColsInsert(const Eigen::MatrixXf &input, Eigen::MatrixXi &output){
    int rows = input.rows();

    for (int col = 0; col < input.cols(); ++col) {
        for (int i = 1; i < rows; ++i) {
            for (int j = i; j>0 && input(output(j, col), col) < input(output(j-1, col), col); --j) {
                int id = output(j, col);
                output(j, col) = output(j-1, col);
                output(j-1, col) = id;
            }
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

std::vector<std::pair<int, int> > getIdx(const Eigen::MatrixXf &input, int type, int thres){
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

void setIdx(Eigen::MatrixXf &input, const std::vector<std::pair<int, int> > &idx, float target){
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
            7795,7816,7838,7859,7881,7902,7924,7945,7967,7988,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,
            8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000,8000;
    IF_INIT = 1;
}
