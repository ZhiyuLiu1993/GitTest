#include <iostream>
#include <algorithm>


using namespace std;

//fibonacci2, no continus 2

class Solution{
public:
    int f(int n){
        if(n == 1)
            return 1;
        if(n == 2)
            return 2;
        int minusOne = 2;
        int minusTwo = 1;
        int sum = 0;
        int del[n];
        del[1] = 0;
        del[2] = 1;
        for (int i = 3; i <= n; ++i) {
            sum = minusOne + minusTwo - del[i-2];
            del[i] = minusTwo - del[i-2];
            minusTwo = minusOne;
            minusOne = sum;
        }
        return sum;
    }
};


int main() {
    Solution a;

    int num;
    cin>>num;

    cout<< a.f(num) <<endl;


    return 0;
}