#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>


using namespace std;

class A{   //sizeof(A)   16
public:
    int a;   //4
    virtual int get(){};  //8
};

class B1: virtual A{  //sizeof(B1)  32
public:
    int b1;    //4
    int get() override {   //8
        return b1;
    }
};

class B2: virtual A{   //if public   sizoef(B2)  16
public:
    int b2;
//    int get() override {  //no unique final overrider for ‘virtual int A::get()’ in ‘C’
//        return b2;
//    }
};

class C: public B1, public B2{   //sizeof(C)  48
public:
    int c;
//    int get() override {
//        return c;
//    }
};


int main() {
//    A *a = new C();   //‘A’ is an inaccessible base of ‘C’
//    cout<<a->get()<<endl;    //no unique final overrider for ‘virtual int A::get()’ in ‘C’
    cout<< sizeof(C) <<endl;
    return (0);
}