#include <iostream>
#include <cstring>


using std::cout;
using std::endl;

bool increment(char *number){
    bool isOverflow = false;
    int nTakeOver = 0;
    int nLength = strlen(number);
    for (int i = nLength - 1; i >= 0; --i) {
        int nSum = number[i] - '0' + nTakeOver;
        if(i == nLength - 1)
            ++nSum;
        if(nSum >= 10){
            if(i == 0){
                isOverflow = true;
                break;
            }
            else{
                nTakeOver = 1;
                number[i] = '0';
            }
        } else{
            number[i] = '0' + nSum;
            break;
        }
    }
    return isOverflow;
}

void printNumber(char *number){
    bool isBeginning0 = true;
    int nLength = strlen(number);
    for (int i = 0; i < nLength; ++i) {
        if(isBeginning0 && number[i] != 0)
            isBeginning0 = false;
        if(!isBeginning0)
            printf("%c", number[i]);
    }
    printf("\n");
}

void printToMaxOfNDigits(int n){
    if(n <= 0)
        return;
    char *number = new char[n+1];
    memset(number, '0', n);
    number[n] = '\0';

    while(!increment(number))
        printNumber(number);
    delete []number;
}

int main(){
    printToMaxOfNDigits(3);
    return 0;
}

