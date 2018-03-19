#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::push_heap;
using std::pop_heap;
using std::less;
using std::greater;

template <typename T> class DynamicArray{
public:
    void Insert(T num){
        if(((min.size() + max.size())& 1) == 0){  //insert num is odd, insert min first
            if(max.size() > 0 && num < max[0]){   //max[0] need less than num
                max.push_back(num);
                push_heap(max.begin(), max.end(), less<T>());

                num = max[0];

                pop_heap(max.begin(), max.end(), less<T>());
                max.pop_back();
            }
            min.push_back(num);
            push_heap(min.begin(), min.end(), greater<T>());
        }else{
            if(min.size() > 0 && min[0] < num){
                min.push_back(num);
                push_heap(min.begin(), min.end(), greater<T>());

                num = min[0];

                pop_heap(min.begin(), min.end(), greater<T>());
                min.pop_back();                      //pop is delete
            }

            max.push_back(num);
            push_heap(max.begin(), max.end(), greater<T>());      //insert need to adjust
        }
    }

    T GetMedian(){
        int size = min.size() + max.size();
        if(size == 0)
            throw new std::exception();

        T median = 0;
        if(size&1)
            return min[0];
        else
            median = (min[0] + max[0]) / 2;
    }

private:
    vector<T> min;
    vector<T> max;
};

int main(){

    return 0;
}

