#include <stdio.h>


#define LOCK_PREFIX "lock "
#define UNLOCK_LOCK_PREFIX

//#define __always_inline 


typedef struct arch_spinlock {
	unsigned int slock;
} arch_spinlock_t;


static __always_inline void __ticket_spin_lock(arch_spinlock_t *lock)
{
	short inc = 0x0100;

	asm volatile (
		LOCK_PREFIX "xaddw %w0, %1\n"
		"1:\t"
		"cmpb %h0, %b0\n\t"
		"je 2f\n\t"
		"rep ; nop\n\t"
		"movb %1, %b0\n\t"
		/* don't need lfence here, because loads are in-order */
		"jmp 1b\n"
		"2:"
		: "+Q" (inc), "+m" (lock->slock)
		:
		: "memory", "cc");
}

static __always_inline void __ticket_spin_unlock(arch_spinlock_t *lock)
{
	asm volatile(UNLOCK_LOCK_PREFIX "incb %0"
		     : "+m" (lock->slock)
		     :
		     : "memory", "cc");
}

int main()
{
	arch_spinlock_t lock = {0};
	int i;
	printf("%d: 0x%x\n", -1, lock.slock);
	for (i = 0; i < 5; i++){
		__ticket_spin_lock(&lock);
		printf("%d: 0x%x\n", i, lock.slock);
		__ticket_spin_unlock(&lock);
		printf("%d: 0x%x\n", i, lock.slock);
	}
	return 0;
}
