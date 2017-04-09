#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void handler(int sig)
{
	sigset_t cur;
	int i;

	if (-1 == sigprocmask(0, NULL, &cur)){
		perror("");
		exit(1);
	}
	
	for (i = 1; i <= 64; i++){
		if (!sigismember(&cur, i)){
			printf("[%d] %s\n", i, (char *)strsignal(i));
		}
	}
}

int main()
{
	signal(3, handler);
	raise(3);
	return 0;
}
