#include <stdio.h>

int main()
{
	asm volatile("");
#ifdef __ASSEMBLY__
	printf("__ASSEMBLY__\n");
#else
	printf("no\n");
#endif
	return 0;
}
