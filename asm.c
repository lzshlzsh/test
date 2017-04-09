#include <stdio.h>

int main()
{
	int a = 1, b = 2;
	asm volatile(
		"movl %[__b], %%eax\n"
		"addl %%eax, %[__a]\n"
		: [__a]"=m"(a)
		: [__b]"m"(b)
		: "eax", "memory"
	);

	fprintf(stderr, "a = %d\n", a);
	return 0;
}
