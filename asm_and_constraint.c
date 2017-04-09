#include <stdio.h>

int foo()
{
	printf("foo called\n");
	return 12;
}
int main()
{
	int ret, bar = 0;
	__asm__ volatile( 
			"call foo\n"
			"movl %%edx,%1\n"
			: "=a"(ret)
			: "r"(bar) );
	printf("ret = %d, bar = %d\n", ret, bar);
return 0;
}

