#include <stdio.h>

int main()
{
	int i = 0x8024;
	int rst = 0;
	asm volatile("bsf %1, %0\n":"=r"(rst):"r"(i));
	printf("first 1 of 0x%x is %d\n", i, rst);
	asm volatile("bsr %1, %0\n":"=r"(rst):"r"(i));
	printf("last 1 of 0x%x is %d\n", i, rst);
	return 0;
}
