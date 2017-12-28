#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <string.h>
#include <typeinfo>

using namespace std;


class Complex
{
private :
    double    m_real;
    double    m_imag;
public:
    Complex(void)
    {
        cout<<1<<endl;
        m_real = 0.0;
        m_imag = 0.0;
    }
    Complex(double real, double imag)
    {
        cout<<2<<endl;
        m_real = real;
        m_imag = imag;
    }
    //    复制构造函数（也称为拷贝构造函数）
    Complex(const Complex & c)
    {
        // 将对象c中的数据成员值复制过来
        cout<<3<<endl;
        m_real = c.m_real;
        m_imag    = c.m_imag;
    }
    // 类型转换构造函数，根据一个指定的类型的对象创建一个本类的对象，
    Complex(double r)
    {
        cout<<4<<endl;
        m_real = r;
        m_imag = 0.0;
    }
    // 等号运算符重载（也叫赋值构造函数）
    Complex &operator=( const Complex &rhs )
    {
        if ( this == &rhs )
        {
            return *this;
        }
        cout<<5<<endl;
        this->m_real = rhs.m_real;
        this->m_imag = rhs.m_imag;
        return *this;
    }
};

int main()
{
    Complex c1,c2; //默认

    cout<<endl;
    Complex c3(1.0,2.5); //一般，第二个
    cout<<endl;
    Complex c31 = Complex(1.0,2.5); //一般，第二个

    cout<<endl;
    c1 = c3;   //赋值
    cout<<endl;
    c2 = 5.2;  //类型转换再赋值
    cout<<endl;
    Complex c5(c2);    //拷贝
    cout<<endl;
    Complex c4 = c2;  //拷贝  注意和 = 运算符重载区分,这里等号左边的对象不是事先已经创建，故需要调用拷贝构造函数，参数为c2
}
