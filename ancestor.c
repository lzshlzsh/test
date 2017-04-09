#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

void abort_handler(int num, siginfo_t *info, void *uc)
{
	printf("[%d] %s received\n", getpid(), strsignal(num));
	fflush(stdout);
}
int main()
{
	struct sigaction sa;
	sa.sa_sigaction = abort_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGABRT, &sa, NULL);

	if (fork()){
		printf("parent: pid %d, ppid %d\n", getpid(), getppid());
		raise(SIGABRT);
	}else{
		printf("child: pid %d, ppid %d\n", getpid(), getppid());
		raise(SIGABRT);
	}
	return 0;
}
