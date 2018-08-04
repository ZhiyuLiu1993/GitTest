#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

//����Ƿ���ͨ
//1��ʾOK
int checkVaild(int x1, int y1, int x2, int y2){
    int tmp = x1 - x2 + y1 - y2;
    if(tmp == -1 || tmp == 1)
        return 1;
    else return 0;
}

//����·
void fillRoad(int x1, int y1, int x2, int y2, vector<vector<char>> &road){
    road[2*x1+1][2*y1+1] = 'R';
    road[2*x2+1][2*y2+1] = 'R';
    if(x1 > x2)
        road[2*x2+2][2*y1+1] = 'R';
    else if(x2 > x1)
        road[2*x1+2][2*y1+1] = 'R';
    else if(y1 > y2)
        road[2*x1+1][2*y2+2] = 'R';
    else if(y2 > y1)
        road[2*x1+1][2*y1+2] = 'R';
}

int main() {
    string input;
    getline(cin, input);
    stringstream ss(input);
    //�Թ��ߴ�
    int row, col;
    ss >> row;
//    cout << row << endl;
    if(ss.fail() || row <= 0){
        cout << "Invalid number format.";
        return -1;
    }
    ss >> col;
    if(ss.fail() || col <= 0){
        cout << "Invalid number format.";
        return -1;
    }
//    cout << col << endl;

    //��Ⱦ����
    vector<vector<char>> road(2*row+1);
    for (int i = 0; i < 2*row+1; ++i) {
        road[i].resize(2*col+1);
    }

    for (int i = 0; i < 2*row+1; ++i) {
        for (int j = 0; j < 2*col+1; ++j) {
            road[i][j] = 'W';
        }
    }

    //��·����
    getline(cin, input);
    //��ȡһ��
//    cout << input.size();
    enum {X = 0, Y, SPACE, BRANCH};   //X��ʾx���꣬Y��ʾy���� , SPACE��ʾ�ո�, BRANCH��ʾ�ֺ�

    int pre = Y;
    int preA = BRANCH;

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;    //��ʾһ���ָ�������������

//    bool done = true;     //��ʾ��������������ɣ�������Ч���ж�  //ͨ��';'�ж�


    x1 = input[0] - '0';
    if(x1 < 0 || x1 > 9){
        cout << "Invalid number format.";
        return -1;
    }

    int tmp;
    for (int i = 1; i < input.size(); ++i) {
        if(preA == BRANCH){
            if(pre == Y) {
                if(input[i] == ','){
                    pre = X;
                    if(x1 >= row){
                        cout << "Number out of range.";
                        return -1;
                    }
                }else {
                    tmp = input[i] - '0';
                    if(tmp < 0 || tmp > 9){
                        cout << "Invalid number format.";
                        return -1;
                    }
                    x1 = x1*10 + tmp;
                }
            }else if(pre == X){
                if(input[i] == ' '){
                    pre = Y;
                    preA = SPACE;
                    if(y1 >= col){
                        cout << "Number out of range.";
                        return -1;
                    }
                } else{
                    tmp = input[i] - '0';
                    if(tmp < 0 || tmp > 9){
                        cout << "Invalid number format.";
                        return -1;
                    }
                    y1 = y1*10 + tmp;
                }
            }
        }else{
            if(pre == Y) {
                if(input[i] == ','){
                    pre = X;
                    if(x2 >= row){
                        cout << "Number out of range.";
                        return -1;
                    }
                }else {
                    tmp = input[i] - '0';
                    if(tmp < 0 || tmp > 9){
                        cout << "Invalid number format.";
                        return -1;
                    }
                    x2 = x2*10 + tmp;
                }
            }else if(pre == X){
                if(input[i] == ';'){
                    pre = Y;
                    preA = BRANCH;
                    if(y2 >= col){
                        cout << "Number out of range.";
                        return -1;
                    }
                    if(!checkVaild(x1, y1, x2, y2)){
                        cout << "Maze format error.";
                        return -1;
                    }
                    fillRoad(x1, y1, x2, y2, road);
                    x1 = y1 = x2 = y2 = 0;
                } else{
                    tmp = input[i] - '0';
                    if(tmp < 0 || tmp > 9){
                        cout << "Invalid number format.";
                        return -1;
                    }
                    y2 = y2*10 + tmp;
                    if(i == input.size()-1){
                        if(!checkVaild(x1, y1, x2, y2)){
                            cout << "Maze format error.";
                            return -1;
                        }
                        fillRoad(x1, y1, x2, y2, road);
                    }
                }
            }
        }
    }


    for (int i = 0; i < 2*row+1; ++i) {
        for (int j = 0; j < 2*col+1; ++j) {
            cout << "[" << road[i][j] << "] ";
        }
        cout << endl;
    }

    return 0;
}


