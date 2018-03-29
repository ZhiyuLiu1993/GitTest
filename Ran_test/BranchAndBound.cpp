#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::for_each;
using std::ostream_iterator;
using std::copy;

//分支限界法，求背包容量

class Solution{
public:
    int BranchAndBound(int max, int cap, int box[]){
        int temp = 0;
        int best = 0;
        int curVal = 0;
        int parentVal = 0;
        int exceptVal = 0;
        int level = -1;
        queue<int> queue1;
        queue1.push(-1);    //-1表示一层
        queue1.push(parentVal);
        while(level != max && !queue1.empty()){
            parentVal = queue1.front();
            queue1.pop();
            if(parentVal != -1){
                //left child
                curVal = parentVal + box[level];
                if(curVal > best && curVal <= cap){
                    best = curVal;
                }
                if(level < max-1 && curVal <= cap)
                    queue1.push(curVal);

                //right child
                temp = 0;
                curVal = parentVal;
                for (int i = level+1; i < max; ++i)
                    temp += box[i];
                exceptVal = curVal + temp;     //如果期望不加上当前level的值，剩下的可能最大值，如果不够则剪枝不加入
                if(exceptVal > best && level < max-1)
                    queue1.push(curVal);
            } else{   //表示当前层结束，需加入结束标志
                if(level < max-1)
                    queue1.push(-1);
                ++level;
            }
        }
        return best;
    }

};


int main(){
    Solution a;
    int arr[] ={10,15,20};
    cout<<a.BranchAndBound(3, 35, arr)<<endl;


    return 0;
}

