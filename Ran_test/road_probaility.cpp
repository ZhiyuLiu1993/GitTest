#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <map>

//城镇概率，在最后一个城镇结束旅程概率
//输入  N（城镇数量)  M(道路)  又能由低编号城镇走向高编号城镇

using namespace std;

int sum = 0;
int nCount = 0;

void probaility(map<int, vector<int>> &road, int node, int final){
    for (int i = 0; i < road[node].size(); ++i) {
        if(road[node][i] == final){
            ++sum;
            ++nCount;
        } else if(road.find(road[node][i]) == road.end()){
            ++sum;
        } else{
            probaility(road, road[node][i], final);
        }
    }
}

int main(){
    int n;
    int m;
    cin >> n >> m;
    map<int, vector<int>> road;
    int src, dst;
    for (int i = 0; i < m; ++i) {
        cin >> src >> dst;
        if(road.find(src) == road.end()){
            road[src] = {dst};
        } else{
            vector<int> tmp = road[src];
            tmp.push_back(dst);
            road[src] = tmp;
        }
    }
    probaility(road, 1, n);

    cout << (double)nCount/sum << endl;

    return 0;
}

