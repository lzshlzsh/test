#include <stdio.h>

static void goo(int size)
{
	int A[size];
	int a = 0;
	a++;
	printf("callee: %p\n", &a);
}
static void foo()
{
	int a = 0;
	a++;
	printf("caller: %p\n", &a);

	goo(100);
}

int main()
{

	foo();
	return 0;
}
