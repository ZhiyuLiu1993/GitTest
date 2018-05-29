#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <sstream>


using namespace std;


class Solution{
public:
    void push(int value) {
        if(sta.empty()){
            minval = value;
            sta.push(0);
        } else if(value < minval){ //如果minval要更新，更新处填的便是minval之间的差值
            int temp = minval;
            minval = value;
            sta.push(value - temp);
        } else{  //否则填的是与minval的差值
            sta.push(value - minval);
        }
    }
    void pop() {
        if(!sta.empty()){
            if(sta.top() < 0){
                minval = minval - sta.top();//更新最小值
                sta.pop();
                return;
            }
            if(sta.top() + minval >= minval){
                sta.pop();
                return;
            }
//            else {//更新最小值
//
//            }
        }else{
            throw std::exception();
        }
    }
    int top() {
        if(!sta.empty()){
            //如果top小于0，说明当前top为最小值
            if(sta.top() < 0)
                return (minval);
            //否则为最小值加上top
            else
                return (minval + sta.top());
        }else{
            throw std::exception();
        }
    }
    int min() {
        if(!sta.empty()){
            return minval;
        }else{
            throw std::exception();
        }
    }
private:
    stack<int> sta;
    int minval;

};

int main() {
    Solution a;
    a.push(3);
    cout<<a.top()<<endl;
    cout<<a.min()<<endl;
    a.push(3);
    cout<<a.top()<<endl;
    cout<<a.min()<<endl;
    a.push(1);
    cout<<a.top()<<endl;
    cout<<a.min()<<endl;
    a.pop();
    cout<<a.top()<<endl;
    cout<<a.min()<<endl;

    return (0);
}
