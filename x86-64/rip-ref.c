#include <stdio.h>


int main()
{
	long addr = 0;

	asm volatile(
	"leaq (%%rip), %%rax\n"
	"movq %%rax, %0\n"
	: "=m"(addr)
	:
	);

	printf("addr = %#lx\n", addr);

	return 0;
}
