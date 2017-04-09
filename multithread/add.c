#include <stdio.h>

static int a = 1;

int main()
{
	asm volatile(
			"addl $1, %0\n"
			: "=m"(a)
			:
			: "memory"
			);
	printf("a = %d\n", a);
	return 0;
}
