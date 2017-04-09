#include <stdio.h>


#define CMPXCHG	\
	asm volatile(	\
			"movl $10, %%eax\n"	\
			"movl $11, %%ebx\n"	\
			"lock cmpxchgl %%ebx, %0\n"	\
			"cmpxchgl %%ebx, %0\n"	\
			: "=m"(a)	\
			:	\
			:"memory"	\
			);


int main()
{
	int a = 10;
//	printf("a = %d\n", a);
#if 1
	asm volatile(
			"movl $10, %%eax\n"
			"movl $11, %%ebx\n"
			"lock cmpxchgl %%ebx, %0\n"
			"cmpxchgl %%ebx, %0\n"
			: "=m"(a)
			:
			:"memory"
			);
#else
	CMPXCHG;
#endif	
	printf("a = %d\n", a);
	return 0;
}
