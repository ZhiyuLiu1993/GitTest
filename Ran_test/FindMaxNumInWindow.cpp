#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::for_each;
using std::ostream_iterator;
using std::copy;

//给定数组和窗口大小，求滑动窗口最大值

class Solution{
public:
    vector<int> FindMaxNumInWindow(int arr[], int length, int size){
        vector<int> maxInWindow;
        deque<int> deque1;
        for (int i = 0; i < size; ++i) {
            while(!deque1.empty() && arr[deque1.back()] < arr[i])
                deque1.pop_back();
            deque1.push_back(i);
        }
        maxInWindow.push_back(arr[deque1.front()]);
        deque1.pop_front();
        for (int j = size; j < length; ++j) {
            while(!deque1.empty() && arr[deque1.back()] < arr[j])
                deque1.pop_back();
            deque1.push_back(j);
            while(!deque1.empty() && (j-deque1.front()>=size))
                deque1.pop_front();
            maxInWindow.push_back(arr[deque1.front()]);
        }
        return maxInWindow;
    }
};


int main(){
    Solution a;

    int arr[] = {1,2,3,5,4,5,13,5};

    vector<int> result = a.FindMaxNumInWindow(arr, 8, 3);

    for_each(result.begin(), result.end(), [](const int &a){cout<<a<<" ";});
    cout<<endl;

    ostream_iterator<int>  out_iter(cout, " ");
    copy(result.begin(), result.end(), out_iter);
    cout<<endl;

    return 0;
}

