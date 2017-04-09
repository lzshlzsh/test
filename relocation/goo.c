#include <stdio.h>

int shared2 = 3;


int goo()
{
	printf("goo called, shared2 = %d\n", shared2);	
	return shared2;
}

