#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <sstream>


using namespace std;


class Solution{
public:
    void Permutation(string Str, int begin){
        if(begin == Str.size()-1){   //-1 才能与下面的+1匹配，否则此条件永远不满足
            cout<<Str<<endl;
        }
        else{
            for(int i = begin+1; i < Str.size(); ++i){   //此处+1  计算的是原字母不在其原始位置上的排列    最终begin就不会到size大小
                char temp = Str[i];
                Str[i] = Str[begin];
                Str[begin] = temp;

                Permutation(Str, begin+1);

                temp = Str[i];
                Str[i] = Str[begin];
                Str[begin] = temp;
            }
        }
    }

};

int main() {
    Solution a;

    string str("abc");

    a.Permutation(str, 0);

    return (0);
}