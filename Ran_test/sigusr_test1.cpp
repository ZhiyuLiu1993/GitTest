#include "apue.h"
#include <iostream>
#include <signal.h>
using namespace std;

void CatchSigUsr1(int sig)
{
    cout<<"SIGUSR1 Caught"<<endl;
}

void CatchSigUsr2(int sig)
{
    cout<<"SIGUSR2 Caught"<<endl;
    exit(0);
}

int main()
{
    signal(SIGUSR1, CatchSigUsr1);
    signal(SIGUSR2, CatchSigUsr2);
    while(1)
    {
        sleep(1);
    }
}
