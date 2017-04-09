#include <signal.h>
#include <stdio.h>

int main()
{
	printf("%d\n", siggetmask());
	return 0;
}
