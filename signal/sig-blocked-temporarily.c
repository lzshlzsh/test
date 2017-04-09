#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


static void handler(int sig, siginfo_t *info, void *uc)
{
	printf("%d received\n", sig);
}

int main()
{
	struct sigaction act;
	sigset_t set;

	act.sa_sigaction = handler;
	sigfillset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	sigemptyset(&set);
	sigaddset(&set, SIGRTMIN);

	if (-1 == sigaction(SIGRTMIN, &act, NULL)){
		printf("sigaction failed\n");
		exit(1);
	}
	if (-1 == sigprocmask(SIG_BLOCK, &set, NULL)){
		printf("sigprocmask failed\n");
		exit(1);
	}

	printf("send many SIGRTMIN(%d)\n", SIGRTMIN);

	raise(SIGRTMIN);
	raise(SIGRTMIN);
	raise(SIGRTMIN);
	raise(SIGRTMIN);

	printf("change sig mask\n");

	if (-1 == sigprocmask(SIG_UNBLOCK, &set, NULL)){
		printf("sigprocmask failed\n");
		exit(1);
	}
	return 0;
}
