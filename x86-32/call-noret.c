#include <stdio.h>

int main()
{
	long addr = 0;

	asm volatile(
	"call 1f\n"
	"addl	$1, %0\n"
	"addl	$1, %0\n"
	"addl	$1, %0\n"
	"1:\n"
	"popl	%%ebx\n"
	"movl	%%ebx, %0\n"
	: "=m"(addr)
	:
	: "memory"
	);

	printf("addr = %#lx\n", addr);
	return 0;
}
