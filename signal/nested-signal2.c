#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <stdlib.h>

#define USER_SIG1 SIGRTMAX
#define USER_SIG2 (SIGRTMAX - 1)


volatile int lock = 0;

static void handler1(int num, siginfo_t *info, void *uc)
{
	pid_t tid = syscall(SYS_gettid);
	sigset_t set;
	fprintf(stdout, "%d [%d] sig received, now I am waiting\n", num, tid);
	sigprocmask(0, NULL, &set);
	if (sigismember(&set, USER_SIG2)){
		printf("%d [%d] sig %d blocked\n", num, tid, USER_SIG2);
	}else{
		printf("%d [%d] sig %d not blocked\n", num, tid, USER_SIG2);
	}
	if (sigismember(&set, USER_SIG1)){
		printf("%d [%d] sig %d blocked\n", num, tid, USER_SIG1);
	}else{
		printf("%d [%d] sig %d not blocked\n", num, tid, USER_SIG1);
	}
//	sleep(1);
	raise(USER_SIG2);
	while(!lock){};
	fprintf(stdout, "%d [%d] I have passed the barrier\n", num, tid);
}

static void handler2(int num, siginfo_t *info, void *uc)
{
	pid_t tid = syscall(SYS_gettid);
	fprintf(stdout, "%d [%d] make handler1 go ahead\n", num, tid);
	lock = 1;
}

int main()
{
	struct sigaction newact;
	pid_t p_tid = syscall(SYS_gettid);

	newact.sa_sigaction = handler1;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = SA_SIGINFO | SA_NODEFER;

	sigaction(USER_SIG1, &newact, NULL);

	newact.sa_sigaction = handler2;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = SA_SIGINFO | SA_NODEFER;

	sigaction(USER_SIG2, &newact, NULL);

	if (! fork()){
		kill(p_tid, USER_SIG1);
//		usleep(1.1);
//		kill(p_tid, USER_SIG2);
		exit(0);
	}

	wait(NULL);

	return 0;
}
