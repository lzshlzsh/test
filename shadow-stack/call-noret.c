#include <stdio.h>

int main()
{
	long addr = 0;

	asm volatile(
	"call 1f\n"
	"addq	$1, %0\n"
	"addq	$1, %0\n"
	"addq	$1, %0\n"
	"1:\n"
	"popq	%%rbx\n"
	"movq	%%rbx, %0\n"
	: "=m"(addr)
	:
	: "memory"
	);

	printf("addr = %#lx\n", addr);
	return 0;
}
