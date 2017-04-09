#include <stdio.h>

int shared1 = 1;
int shared2 = 2;


int foo()
{
	printf("foo called, shared1 = %d\n", shared1);	
	return shared1;
}

