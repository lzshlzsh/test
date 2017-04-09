/*
 *Created Time: 2009-07-31 20:54:44
 *Last Modified: 2009-07-31 20:54:44
 *File Name: add.c
 *Description: 
 */
#include <stdio.h>
int main()
{
	int a = 0, b = -1;

	printf("%d + %d = ", a, b);
	__asm__ __volatile__(
				"addl %1, %2\n"
				:"=m"(a)
				:"r"(b), "0"(a)
				);
	printf("%d\n", a);
	printf("%d + %d = ", a, b);
	asm volatile(
				"addl %1, %0\n"
				:"+m"(a)
				:"r"(b)
				);
	printf("%d\n", a);
	return 0;
}
