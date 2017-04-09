#include <stdio.h>

int my(int a)
{
	static int count = a;
	return (count + a);
}

int main()
{
	printf("%d %d\n", my(4), my(5));
	return 0;
}
