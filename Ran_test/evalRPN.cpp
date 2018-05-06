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

    return (0);
}