#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sched.h>


char *strsignal(int sig);

static void handler(int signum)
{
	printf("[%ld]sig %d received\n", syscall(SYS_gettid), signum);
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
	syscall(SYS_tkill, getpid(), 64);
	syscall(SYS_tgkill, getpid(), syscall(SYS_gettid), 64);
	

	if (!(child = fork())){
		signal(2, handler);
		sigaddset(&mask, 1);
		sigsuspend(&mask);
		exit(0);
	}
	
	syscall(SYS_tkill, child, 28);
	sleep(1);
//	syscall(SYS_tkill, child, 11);
	syscall(SYS_tkill, child, 2);

	wait(NULL);

	return 0;
}
