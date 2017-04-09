#ifndef _ASM_I386_RWLOCK_H
#define _ASM_I386_RWLOCK_H

#define RW_LOCK_BIAS		 0x01000000
#define RW_LOCK_BIAS_STR	"0x01000000"
#define LOCK "lock "

#define __build_read_lock_ptr(rw, helper)   \
	asm volatile(LOCK "subl $1,(%0)\n\t" \
			"js 2f\n" \
			"1:\n" \
			".section .text.lock,\"ax\"\n" \
			"2:\tcall " helper "\n\t" \
			"jmp 1b\n" \
			".previous" \
			::"a" (rw) : "memory")

#define __build_read_lock_const(rw, helper)   \
			asm volatile(LOCK "subl $1,%0\n\t" \
					"js 2f\n" \
					"1:\n" \
					".section .text.lock,\"ax\"\n" \
					"2:\tpushl %%eax\n\t" \
					"leal %0,%%eax\n\t" \
					"call " helper "\n\t" \
					"popl %%eax\n\t" \
					"jmp 1b\n" \
					".previous" \
					:"=m" (*(volatile int *)rw) : : "memory")

#define __build_read_lock(rw, helper)	do { \
	if (__builtin_constant_p(rw)) \
	__build_read_lock_const(rw, helper); \
	else \
	__build_read_lock_ptr(rw, helper); \
} while (0)

#define __build_write_lock_ptr(rw, helper) \
					asm volatile(LOCK "subl $" RW_LOCK_BIAS_STR ",(%0)\n\t" \
							"jnz 2f\n" \
							"1:\n" \
							".section .text.lock,\"ax\"\n" \
							"2:\tcall " helper "\n\t" \
							"jmp 1b\n" \
							".previous" \
							::"a" (rw) : "memory")

#define __build_write_lock_const(rw, helper) \
							asm volatile(LOCK "subl $" RW_LOCK_BIAS_STR ",(%0)\n\t" \
									"jnz 2f\n" \
									"1:\n" \
									".section .text.lock,\"ax\"\n" \
									"2:\tpushl %%eax\n\t" \
									"leal %0,%%eax\n\t" \
									"call " helper "\n\t" \
									"popl %%eax\n\t" \
									"jmp 1b\n" \
									".previous" \
									:"=m" (*(volatile int *)rw) : : "memory")

#define __build_write_lock(rw, helper)	do { \
	if (__builtin_constant_p(rw)) \
	__build_write_lock_const(rw, helper); \
	else \
	__build_write_lock_ptr(rw, helper); \
} while (0)

#endif

#include <stdio.h>		

static void helper()
{
	printf("helper\n");
}

int main()
{
	int a, *rw = &a;

	__build_write_lock(rw, "helper");

	return 0;
}
