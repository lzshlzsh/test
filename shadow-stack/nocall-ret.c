#include <stdio.h>

static void foo()
{
	printf("hello world\n");
}

int main()
{
	asm volatile (
	"leaq	1f, %%rbx\n"
	"pushq	%%rbx\n"
	"jmpq	*%0\n"
	"1:\n"
	:
	: "r"(foo)
	: "memory"
	);
	return 0;
}
