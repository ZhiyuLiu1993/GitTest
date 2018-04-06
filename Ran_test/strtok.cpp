#include <iostream>
#include <cassert>

using namespace std;


char *strtok(char *strToken, const char *str){
    assert(str != NULL);
    static char *last;

    if (strToken == NULL && (strToken = last) == NULL)
        return (NULL);

    char *s = strToken;
    const char *t = str;
    while (*s != '\0')
    {
        t = str;
        while (*t != '\0')
        {
            if (*s == *t)
            {
                last = s + 1;
                if (s - strToken == 0) {
                    strToken = last;             //delete the pre char impact
                    break;
                }
                *(strToken + (s - strToken)) = '\0';
//                *s = '\0';
                return strToken;
            }
            ++ t;
        }
        ++ s;
    }
    return NULL;
}

int main() {
//    char buf[]="hello@boy@this@is@heima";
    char buf[] = "ab-cd : ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
    char*temp = strtok(buf,"-: ");
    while(temp)
    {
        printf("%s ",temp);
        temp = strtok(NULL,"-: ");
    }
    return 0;
}