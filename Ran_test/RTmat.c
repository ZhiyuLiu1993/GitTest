#include <stdio.h>
#include <math.h>
#include "image.h"
/*
 * 输出:mat为旋转矩阵
 * 输入:dst为匹配图模板质心
 * 输入:src为模板图模板质心
 * 输入:angel为模板到匹配图旋转角度
 * */
void compute_trmat(TRMat *mat, IPointf src, IPointf dst, int angel)
{
    const double pi = acos(-1.0);
    double xa;
    xa = angel*pi/180;
    mat->tx = dst.x - src.x;
    mat->ty = dst.y - src.y;
    mat->cosa = cos(xa);
    mat->sina = sin(xa);
}

/*
 * 输入:mat为旋转矩阵
 * 输入:模板上的点
 * 输出:待测图上的点
 * */
void compute_cord(TRMat mat, IPointf model, IPointf *detect)
{
    detect->x = mat.cosa * model.x - mat.sina * model.y + mat.tx;
    detect->y = mat.sina * model.x + mat.cosa * model.y + mat.ty;
}

int main()
{
    TRMat mat;
    int angel = 90;
    IPointf src = {.x = 40, .y = 40}; //模板上的质心
    IPointf dst = {.x = 50, .y = 50}; //匹配图上的质心

    compute_trmat(&mat, src, dst, angel);

    IPointf m = {.x = 10, .y = 10};
    IPointf d;

    compute_cord(mat, m, &d);

    printf("x:%f,y:%f\n", d.x, d.y);


}
