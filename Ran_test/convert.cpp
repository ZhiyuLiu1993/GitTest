#include <iostream>
#include <algorithm>

// 整数到字符串的转换 ,需编译器支持向0取整
void convert(char buf[], int value){
    static char digits[19] =
            {
                    '9', '8', '7', '6', '5', '4', '3', '2', '1', '0',
                    '1', '2', '3', '4', '5', '6', '7', '8', '9'
            };
    static const char *zero = digits + 9;   //zero point '0'

    //works for int32
    int i = value;
    char *p = buf;
    do{
        int lsd = i % 10;
        i /= 10;
        *p++ = zero[lsd];
    }while(i != 0);

    if(value < 0){
        *p++ = '-';
    }
    *p = '\0';
    std::reverse(buf, p);
}

int main(){
    char tmp[50];
    convert(tmp, -435345);
    printf("%s\n", tmp);
    convert(tmp, 435345);
    std::cout<<tmp<<std::endl;

    return 0;
}
