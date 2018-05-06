#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <sstream>


using namespace std;

class Solution{
public:
     int evalRPN(vector<string> &tokens){
         stack<int> sta;
         for(const auto &tok: tokens){
             if(tok == "+" || tok == "-" || tok == "*" || tok == "/"){
                 int a = sta.top();
                 sta.pop();
                 int b = sta.top();
                 sta.pop();
                 int c;
                 if(tok == "+")
                     c = b + a;
                 else if(tok == "-")
                     c = b - a;
                 else if(tok == "*")
                     c = b * a;
                 else if(tok == "/")
                     c = b / a;
                 sta.push(c);
             }
             else{
                 stringstream ss;   /// *****string to int, ip transform
                 ss<<tok;
                 int temp;
                 ss>>temp;
                 sta.push(temp);
             }
         }
         return sta.top();
     }
};

int main() {
    string str("192.168.1.2");
    stringstream ss;
    ss<<str;
    int p1, p2, p3, p4;
    char a;
    ss>>p1;
    ss>>a;
    ss>>p2;
    ss>>a;
    ss>>p3;
    ss>>a;
    ss>>p4;
    cout<<p1<<" "<<p2<< " "<<p3<<" "<<p4<<endl;

    return (0);
}