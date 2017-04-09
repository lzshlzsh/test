#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sched.h>


static void handler(int signum)
{
	fprintf(stderr, "sig %d received\n", signum);
}
int main()
{
	sigset_t mask;
	pid_t child;
	if (SIG_ERR == signal(64, handler)){
		fprintf(stderr, "%s", strsignal(64));
		perror("");
		exit(1);
	}

	kill(getpid(), 64);

	return 0;
}
