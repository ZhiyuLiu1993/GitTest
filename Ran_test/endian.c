#include <stdio.h>

int main(){
	union endian{
		short a;
		char b[2];
	} test;
	test.a = 0x1234;	
	//test.b[1] = 0x34;	
	union endian2{
		short a;
		char b;
	} test1;

	//little
	test1.a = 1;
	if(test1.a == test1.b)
		printf("little endian\n");

	printf("b[0]:%x.\n", test.b[0]);
	return 0;
}
