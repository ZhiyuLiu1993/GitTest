#include <stdlib.h>
#include <stdio.h>

int main(){
	int *t = NULL;
	int *a = new int(1);
	printf("a:%p------------>%d\n", a, __LINE__);
	int *b = new int(1);
	printf("b:%p------------>%d\n", b, __LINE__);
	int *c = new int(1);
	printf("c:%p------------>%d\n", c, __LINE__);
	int *d = new int(1);
	printf("d:%p------------>%d\n", d, __LINE__);
	*((int **)a) = t;
	t = a;
	printf("a:%p------------>%d\n", a, __LINE__);
	*((int **)b) = t;
	t = b;
	printf("b:%p------------>%d\n", b, __LINE__);
	*((int **)c) = t;
	t = c;
	printf("c:%p------------>%d\n", c, __LINE__);
	*((int **)d) = t;
	t = d;
	printf("d:%p------------>%d\n", d, __LINE__);

	int *s = t;
	t = *((int **)t);
	printf("t:%p------------>%d\n", t, __LINE__);
	t = *((int **)t);
	printf("t:%p------------>%d\n", t, __LINE__);
	t = *((int **)t);
	printf("t:%p------------>%d\n", t, __LINE__);
	t = *((int **)t);
	printf("t:%p------------>%d\n", t, __LINE__);
	//t = *((int **)t);
	//printf("t:%p------------>%d\n", t, __LINE__);

}
