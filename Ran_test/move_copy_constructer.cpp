#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class strvec
{
public:
    strvec() = default;
    strvec(int i, int *p, vector<int> v): mi(i), ps(p), vec(v){cout<<00<<endl;}
    strvec(const strvec &str);
    strvec(strvec &&str);
//    strvec sorted() &&;
//    strvec sorted() const &;
private:
    int mi;
    int *ps;
    vector<int> vec;
};

strvec::strvec(const strvec &str)
{
    cout<<"strvec copy"<<endl;
    mi = str.mi;
    ps = str.ps;
    vec = str.vec;
}

strvec::strvec(strvec &&str)
{
    cout<<"strvec move"<<endl;
    mi = std::move(str.mi);
    ps = std::move(str.ps);
    vec = std::move(str.vec);
}

//strvec strvec::sorted() const &
//{
//    cout<<"strvec sorted const"<<endl;
//    return strvec(*this).sorted();
//}
//
//strvec strvec::sorted() &&
//{
//    cout<<"strvec sorted"<<endl;
//    sort(vec.begin(), vec.end());
//    return *this;
//}

int main() {
    vector<int> a = {1, 2, 5, 2, 4, 5, 7, 2};
    int ss = 10;
    strvec v1(1, &ss, a);//simple
    strvec v2(v1); //copy
    strvec v3(strvec(2, &ss, a)); //simple
    strvec v4(std::move(v2)); //move
    return 0;
}