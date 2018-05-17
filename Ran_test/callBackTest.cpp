#include <iostream>
#include <functional>

using namespace std;

class testCallback{
public:
    testCallback(int i, double d): i_(i), d_(d){}

    using myCallback = std::function<void(int, double)>;
    void AddCallBack(myCallback call){
        cal_ = call;
    }

    void use(){
        cal_(i_, d_);
    }

private:
    myCallback cal_;
    int i_;
    double d_;
};

//普通函数
void normalFunc(int i, double d){
    cout << "normal func:" <<endl;
    cout << i << ":" << d << endl;
}

//lambda
auto lambdaFunc = [](int i, double d){
    cout << "lambda func:" <<endl;
    cout << i << ":" << d << endl;
};

//仿函数
class fakeFunc{
public:
    void operator()(int i, double d) {
        cout << "fake func:" << endl;
        cout << i << ":" << d << endl;
    }
};

//类成员函数
class callbackFunc{
public:
    void classMemFunc(int i, double d){
        cout << "class mem func:" <<endl;
        cout << i << ":" << d << endl;
    }

    static void classMemStaticFunc(int i, double d){
        cout << "class static mem func:" <<endl;
        cout << i << ":" << d << endl;
    }

};



int main(){
    testCallback a(1, 2.0);

    //以下两种方法均可,加入bind可调整参数顺序
//    a.AddCallBack(::std::bind(normalFunc, ::std::placeholders::_1, ::std::placeholders::_2));
    a.AddCallBack(normalFunc);
    a.use();

    a.AddCallBack(lambdaFunc);
    a.use();

    a.AddCallBack(fakeFunc());
    a.use();

    //类普通成员函数需要使用bind函数，并且需要实例化对象，第二个参数传入实例化对象地址，成员函数要加取地址符
    callbackFunc cal;
    a.AddCallBack(::std::bind(&callbackFunc::classMemFunc, &cal, ::std::placeholders::_1, ::std::placeholders::_2));
    a.use();

    //类静态成员函数类似普通函数
    a.AddCallBack(callbackFunc::classMemStaticFunc);
    a.use();
    return 0;
}
