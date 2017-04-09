#include <stdio.h>
#include <unistd.h>

static void foo()
{
	printf("helloworld\n");
}


int main()
{
	foo();
	foo();
	foo();
	foo();

	return 0;
}
