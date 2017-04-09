#include <stdio.h>

typedef struct { volatile int counter; } atomic_t;
typedef int spinlock_t;

#define atomic_read(v)		((v)->counter)

int atomic_dec_and_lock(atomic_t *atomic, spinlock_t *lock)
{
	int counter;
	int newcount;

repeat:
	counter = atomic_read(atomic);
	newcount = counter-1;

	if (!newcount)
		goto slow_path;

	asm volatile("lock; cmpxchgl %1,%2"
		:"=a" (newcount)
		:"r" (newcount), "m" (atomic->counter), "0" (counter));

	/* If the above failed, "eax" will have changed */
	if (newcount != counter)
		goto repeat;
	return 0;
slow_path:
	return 0;
}

int main()
{
	return 0;
}
