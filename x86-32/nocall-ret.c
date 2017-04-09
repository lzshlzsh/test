#include <stdio.h>

static void foo()
{
	printf("hello world\n");
}

int main()
{
	asm volatile (
	"leal	1f, %%ebx\n"
	"pushl	%%ebx\n"
	"jmpl	*%0\n"
	"1:\n"
	:
	: "r"(foo)
	: "memory"
	);
	return 0;
}
