#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>


static void handler_sigint(int sig, siginfo_t *info, void *uc)
{
	printf("sig %d(%s) received\n", sig, strsignal(sig));
}
int main()
{
	struct sigaction act;

	act.sa_sigaction = (void *)handler_sigint;
	sigfillset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	if (-1 == sigaction(64, &act, NULL)){
		perror("sigaction err:");
		exit(-1);
	}
	while(1){}	
	return 0;
}

