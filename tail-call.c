#include <stdio.h>

static void goo(int a, int b, int c, int d)
{
	c++;
	d++;
	printf("c = %d\n", c, d);
}


static void foo(int e, int d, int a, int b, int c)
{
	goo(e, d, a, b);
}
int main()
{
	foo(4, 1, 2, 3, 5);
	return 0;
}
