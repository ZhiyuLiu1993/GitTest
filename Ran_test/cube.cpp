#include <iostream>
#include <algorithm>


using namespace std;

struct magicEntry{
    int score;
    int time;
    double c;
};

class Solution{
public:
    static bool compare(magicEntry m1, magicEntry m2){
        if (equal(m1.c, m2.c))
            return m1.score > m2.score;
        return m1.c > m2.c;
    }

    void Magic(int num, magicEntry magicEntry1[], int total){
        sort(magicEntry1, magicEntry1 + num, compare);

        int max = 0;
        for (int i = 0; i < num; ++i) {
            if(total >= magicEntry1[i].time){
                total -= magicEntry1[i].time;
                max += magicEntry1[i].score;
            }
            cout<<magicEntry1[i].c << " "<< magicEntry1[i].score << " "  <<magicEntry1[i].time << " " << total << endl;
        }
        cout<<max<<endl;
    }

    static bool equal(double d1, double d2){
        return abs(d1 - d2) < 0.000001;
    }
};


int main() {
    Solution a;

    int num;
    cin>>num;
    magicEntry magicEntry1[num];
    int total;
    for (int i = 0; i < num; ++i) {
        cin >> magicEntry1[i].score;
    }
    for (int i = 0; i < num; ++i) {
        cin >> magicEntry1[i].time;
        magicEntry1[i].c = (double)magicEntry1[i].score / (double)magicEntry1[i].time;
    }
    cin>>total;

    a.Magic(num, magicEntry1, total);


    return 0;
}