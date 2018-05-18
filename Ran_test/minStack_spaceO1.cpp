#include <iostream>
#include <stack>

using namespace std;

//不使用辅助栈，空间复杂读为O(1),minval存储当前最小值，栈里存储的值都是与当前值minval的差值，均大于等于0

class Solution {
public:
    void push(int value) {
        if(sta.empty() || value < minval){
            minval = value;
            sta.push(0);
        }else{
            sta.push(value - minval);
        }
    }
    void pop() {
        if(!sta.empty()){
            if(sta.top() + minval == minval){
                sta.pop();
                minval = sta.top() + minval;
                return;
            }
            if(sta.top() + minval > minval){
                sta.pop();
                return;
            }
        }else{
            throw std::exception();
        }
    }
    int top() {
        if(!sta.empty()){
            return (sta.top() + minval);
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

int main(){

    return 0;
}
