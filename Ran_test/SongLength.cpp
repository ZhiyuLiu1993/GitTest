#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <map>

//小Q有X首长度为A的不同的歌和Y首长度为B的不同的歌，现在小Q想用这些歌组成一个总长度正好为K的歌单，
//每首歌最多只能在歌单中出现一次，在不考虑歌单内歌曲的先后顺序的情况下，请问有多少种组成歌单的方法。
using namespace std;

long long c[101][101];   //全局区已初始化为0
const int mod = 1000000007;

//计算组合数  i是下标，j是上标
void init(){
    c[0][0] = 1;
    for (int i = 1; i <= 100; ++i) {
        c[i][0] = 1;
        for (int j = 1; j <= 100; ++j) {
            c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
        }
    }
}

int main(){
    int k;
    int a, b, x, y;   //长度为a和b的歌，a和b的歌分别有x、y首
    long long res = 0;
    init();

    scanf("%d", &k);
    scanf("%d%d%d%d", &a, &b, &x, &y);
    for (int i = 0; i <= x; ++i) {
        if(i*a <= k && (k-i*a)%b == 0 && (k-i*a)/b <= y){
            res =(res + (c[x][i]*c[y][(k-i*a)/b]) % mod) % mod;
        }
    }

    printf("%lld\n", res);

    return 0;
}

