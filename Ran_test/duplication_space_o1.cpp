#include <iostream>

//空间复杂度：O(1);时间复杂度：O(n)
//长度为n的数组里所有数字都在0～n-1范围里，找出一个任意重复数字
bool duplication_spaceo1(int numbers[], int length, int *duplication){
    if(numbers == nullptr || length < 1){
        return false;
    }

    for (int i = 0; i < length; ++i) {
       if(numbers[i] < 0 || numbers[i] > length - 1)
           return false;
    }

    for (int j = 0; j < length; ++j) {
        while(numbers[j] != j){
            if(numbers[numbers[j]] == numbers[j]){   //如果当前数字下标位置不符合但与目标下标位置相同则表示重复
                *duplication = numbers[j];
                return true;
            }

            int temp = numbers[j];
//            numbers[j] = numbers[temp];
            numbers[j] = numbers[numbers[j]];
            numbers[temp] = temp;
//            numbers[numbers[j]] = temp;  //此处一定要使用临时变量
        }
    }
    return false;
}

using std::boolalpha;

int main(){
    int duplicatiuon;
    bool ret;

    int numbers1[] = {1, 0, 3, 2, 2, 5};
    ret = duplication_spaceo1(numbers1, 6, &duplicatiuon);
    std::cout<<boolalpha<<ret<<std::endl;
    if(ret)
        std::cout<<"dup:"<<duplicatiuon<<std::endl;

    int numbers2[] = {1, 0, 3, 4, 2, 5};
    ret = duplication_spaceo1(numbers2, 6, &duplicatiuon);
    std::cout<<boolalpha<<ret<<std::endl;
    if(ret)
        std::cout<<"dup:"<<duplicatiuon<<std::endl;

    int numbers3[] = {-2, 0, 3, 4, 2, 5};
    ret = duplication_spaceo1(numbers3, 6, &duplicatiuon);
    std::cout<<boolalpha<<ret<<std::endl;
    if(ret)
        std::cout<<"dup:"<<duplicatiuon<<std::endl;

    return 0;
}