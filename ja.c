#include <stdio.h>


int main()
{
#if 0	
	int i;
	asm volatile(
			"movl $-1, %%eax\n"
			"subl $-2, %%eax\n"
			"jg 1f\n"
			"movl $0, %0\n"
			"jmp 2f\n"
			"1:\n"
			"movl $1, %0\n"
			"2:\n"
			:"=m"(i)
			:
			:"eax", "memory"
			);

	printf("%d\n", i);
#endif	
	asm volatile(
			"movl 0x123, %eax\n"
			);
	return 0;
}
