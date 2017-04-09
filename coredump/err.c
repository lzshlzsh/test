#include <stdio.h>

static void error()
{
	*(int *)0 = 0;
}

int main()
{
	
	error();

	return 0;
}
