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
        if(sta.empty() || value < minval){
            int temp = minval;
            minval = value;
            sta.push(value - temp);
        }else{
            sta.push(value - minval);
        }
    }
    void pop() {
        if(!sta.empty()){
            if(sta.top() < 0){
                minval = minval - sta.top();
                sta.pop();
                return;
            }
            if(sta.top() + minval > minval){
                sta.pop();
                return;
            }
            else {//更新最小值

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

int main() {
    Solution a;
    a.push(3);
    cout<<a.min()<<endl;
    a.push(2);
    cout<<a.min()<<endl;
    a.push(1);
    cout<<a.min()<<endl;
    a.pop();
    cout<<a.min()<<endl;

    return (0);
}
