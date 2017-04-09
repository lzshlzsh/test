#include <stdio.h>

int main()
{
	double f1 = 2.34, f2 = 1.23;

	asm volatile(
			"faddl %1\n"
			"fadd %%st(0)\n"
			"fsin \n"
			: "+&t"(f1)
			: "m"(f2)
			: "memory"
			);
	printf("f1 = %f\n", f1);
	return 0;
}
