#include <stdio.h>

#define ITETRATION (80 * (1 << 20))

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
		func();
	}
	return 0;
}
