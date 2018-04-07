#include <iostream>

using namespace std;

int gcd(int a, int b){
    int r = a % b;
    while(r != 0){
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

void rotate(string &str, int k_rotate){
    int n = str.size();
    int k = k_rotate;
    int d = gcd(n,k);

    for (int i = 0; i < d; ++i) {
        char tmp = str[i];
        int last = i;

        for (int j = (i + k) % n; j != i; j = (j + k) % n) {
            str[last] = str[j];
            last = j;
        }
        str[last] = tmp;
    }
}
string LeftRotateString(string str, int n) {
    rotate(str, n);
    return str;
}
int main() {

    string str = {"abcXYZdef"};

    cout<<LeftRotateString(str, 3)<<endl;

    return 0;
}