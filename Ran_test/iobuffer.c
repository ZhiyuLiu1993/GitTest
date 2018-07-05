#include <stdio.h>  
#include <unistd.h>  
  
int main()  
{  
	int i=10,pid;  

	printf("nBefor fork.\n");  
	//fflush(stdout);  

	if((pid=fork())<0)  
	{  
		printf("nError fork!");  
		return 1;  
	}  
	else if(pid==0)  
		i++;  
	else  
		sleep(2);  

	printf("ni=%d\n",i);  
	return 0;  
}
