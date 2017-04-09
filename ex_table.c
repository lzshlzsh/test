#include <stdio.h>
#include <string.h>

#define __copy_user(to,from,size)					\
do {									\
	int __d0, __d1;							\
	__asm__ __volatile__(						\
		"0:	rep; movsl\n"					\
		"	movl %3,%0\n"					\
		"1:	rep; movsb\n"					\
		"2:\n"							\
		".section .fixup,\"ax\"\n"				\
		"3:	lea 0(%3,%0,4),%0\n"				\
		"	jmp 2b\n"					\
		".previous\n"						\
		".section __ex_table,\"a\"\n"				\
		"	.align 4\n"					\
		"	.long 0b,3b\n"					\
		"	.long 1b,2b\n"					\
		".previous"						\
		: "=&c"(size), "=&D" (__d0), "=&S" (__d1)		\
		: "r"(size & 3), "0"(size / 4), "1"(to), "2"(from)	\
		: "memory");						\
} while (0)


int main()
{
	char *str1 = "hello world";
	char str2[100];
	int size = strlen(str1);
	__copy_user(str2, str1, size);
	printf("%s\n", str2);
	return 0;
}
