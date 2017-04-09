#include <stdio.h>

#define ITETRATION 0x10000000

static void foo()
{
	int i = 0;
	i++;
//	printf("hello world\n");
}

int main()
{
	int i;

	void (*func)() = foo;
	
	for (i = 0; i < ITETRATION; i++){
		foo();
	}
	return 0;
}
