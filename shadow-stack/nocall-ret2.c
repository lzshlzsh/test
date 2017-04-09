#include <stdio.h>
#include <setjmp.h>

static jmp_buf buf;

static void goo()
{
	longjmp(buf, 1);
}

static void foo()
{
	printf("hello world\n");

	if (!setjmp(buf)){
		goo();
	}
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
