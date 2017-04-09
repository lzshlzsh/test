#include <stdio.h>


/*
 * @return functtion pointer, prototype: void func (int)
 */

static void (* tst_setup_signal(int sig, void (*handler) (int))) (int)
{
	printf("%d, %#x\n", sig, (int)handler);
	return handler;
}

static void handler(int n)
{
}

int main()
{
	printf("%#x\n", (int)tst_setup_signal(2, handler));
	return 0;
}
