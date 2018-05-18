#include <iostream>
#include <stack>

//根据上排给出一些数字，在其下排填出对应的数字
//下排每个数都是上排数字在下排出现的次数
//example:
// top:    0 1 2 3 4 5 6 7 8 9
//bottom : 6 2 1 0 0 0 1 0 0 0

using namespace std;
#define LEN 6

class NumberTB
{
private:
    int top[LEN];
    int bottom[LEN];
    bool success;
public:
    NumberTB();
    void getResult();
    void setNextBottom();
    int getFrequecy(int num);
    void print();
};

NumberTB::NumberTB()
{
    //initialization
    success = false;
    for(int i=0; i<LEN; ++i)
    {
        cin >> top[i];
        bottom[i] = -1;
    }
}

void NumberTB::getResult()
{
    while(!success)
        setNextBottom();
}

void NumberTB::setNextBottom()
{
    bool flag = true;
    int frequency;
    for(int i=0; i<LEN; ++i)
    {
        frequency = getFrequecy(top[i]);
        if( bottom[i] != frequency)
        {
            bottom[i] = frequency;
            flag = false;
        }
    }
    success = flag;
}

int NumberTB::getFrequecy(int num)
{
    int frequecy=0;
    for(int i=0; i<LEN; i++)
        if (bottom[i] == num)
            frequecy++;
    return frequecy;
}

void NumberTB::print()
{
    for(int i=0; i<LEN; i++)
        cout << top[i] << " ";
    cout << endl;

    for(int i=0; i<LEN; i++)
        cout << bottom[i] << " ";
    cout << endl;
}

int main()
{
    NumberTB numtb;

    numtb.getResult();

    numtb.print();

    return 0;
}

