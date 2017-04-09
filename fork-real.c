#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>


void sigint_handler(int signum, siginfo_t *info, void *uc)
{
	printf("[%d]%s received\n", getpid(), strsignal(signum));
}

int main()
{
	struct sigaction act;
	act.sa_sigaction = sigint_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	if (sigaction(SIGINT, &act, NULL) < 0){
		perror("sigaction");
		exit(1);
	}
	if (!fork()){
		while (1){}
		exit(0);
	}
//	while(1){}
	return 0;
}
