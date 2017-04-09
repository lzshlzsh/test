#include <stdio.h>

int main()
{
	int a = 0;
	asm volatile(
			"addl $1, %0\n"
			:
			:"m"(a)
			:"memory"
			);
	printf("a = %d\n", a);
	return 0;
}
