#include <stdio.h>
#include "header.h"

int shared1 = 4;

int main()
{
	foo();
	goo();
	
	printf("main, shared1 = %d\n", shared1);

	return 0;
}
