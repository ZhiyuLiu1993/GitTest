#include<mcheck.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    #ifdef DEBUG
        mtrace();
    #endif
    int *a = NULL;
    a = malloc(sizeof(int));
   //在这里我们不调用free函数
    return 0;
}
