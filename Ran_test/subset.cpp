#include <iostream>
#include <vector>
#include <limits>

using namespace std;

template <typename T>
class Solution{
public:
    void print(T a[], bool marks[], int length){
        bool allFalse = true;
        for (int i = 0; i < length; ++i) {
            if(marks[i]){
                allFalse = false;
                cout<<a[i]<<" ";
            }
        }
        if(allFalse){
            cout<<"null";
        }
        cout<<endl;
    }

    void subset(T a[], bool marks[], int m, int n, int length){
        if(m > n)
            print(a, marks, length);
        else{
            marks[m] = true;
            subset(a, marks, m+1, n, length);
            marks[m] = false;
            subset(a, marks, m+1, n, length);
        }
    }
};

int main() {
    Solution<char> a;

    char temp[] = {'a', 'b', 'c', 'e'};

    bool *marks = new bool(4);

    a.subset(temp, marks, 0, 3, 4);

    return 0;
}