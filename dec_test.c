#include <stdio.h>

struct lock_t
{
	volatile int counter;
};

#define atomic_read(lock) (lock->counter)

int main()
{
	struct lock_t lock = {2}, *atomic = &lock;	
	int counter, newcount;
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

slow_path:	
	return 0;
}
