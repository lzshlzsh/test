#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

#define USER_SIG1 64
#define USER_SIG2 63


static volatile int lock = 0;
static void spin_lock()
{
	while(lock){}
	lock = 1;
}
static void spin_unlock()
{
	lock = 0;
}

//dead lock
static void handler1(int num, siginfo_t *info, void *uc)
{
	static int i = 0;
	int sig = (USER_SIG1 == num) ? USER_SIG2 : USER_SIG1;

	fprintf(stderr, "[%d] try to get lock\n", i);
	spin_lock();
	fprintf(stderr, "sig: %d\n", num);
	if (i < 3){
		kill(getpid(), sig);
	}

	spin_unlock();
	fprintf(stderr, "[%d] unlock\n", i);
	i++;
}

/*static void handler2(int num, siginfo_t *info, void *uc)
{
}*/

int main()
{
	struct sigaction newact;
	pid_t pid_prt;

	newact.sa_sigaction = handler1;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = SA_SIGINFO;

	sigaction(USER_SIG1, &newact, NULL);

	newact.sa_sigaction = handler1;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = SA_SIGINFO;

	sigaction(USER_SIG2, &newact, NULL);

	pid_prt = getpid();

	kill(pid_prt, USER_SIG1);

/*	if (!fork()){
		kill(pid_prt, USER_SIG1);
		kill(pid_prt, USER_SIG1);
		kill(pid_prt, USER_SIG1);
		kill(pid_prt, USER_SIG1);
		exit(0);
	}*/

//	sleep(3);
	return 0;
}
