#define _GNU_SOURCE
#include <sched.h>
#include <sys/types.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <signal.h>

static void csig_handler(int sig, siginfo_t *info, void *context)
{
	printf("child %ld received SIG %d\n", syscall(SYS_gettid), sig);
}

static void psig_handler(int sig, siginfo_t *info, void *context)
{
	printf("parent %ld received SIG %d\n", syscall(SYS_gettid), sig);
}

static int child(void *arg)
{
	struct sigaction act;
	int tid = syscall(SYS_gettid);

	printf("child thread %d\n", tid);

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = csig_handler;
	sigaction(SIGINT, &act, NULL);

	syscall(SYS_tkill, tid, SIGINT);
	syscall(SYS_tkill, tid, SIGINT);

	return 0;
}


int main()
{
	int ctid, tid;
	int sync_clone;
	char cstack[4 << 10];

	tid = syscall(SYS_gettid);
	printf("parent thread %d\n", tid);

	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = psig_handler;
	sigaction(SIGINT, &act, NULL);

	ctid = clone(child, &cstack[(4 << 10) -1], SIGCHLD |
				CLONE_PARENT_SETTID | 
				CLONE_CHILD_CLEARTID /*| CLONE_THREAD*/, NULL, &sync_clone, 
				NULL, &sync_clone);

	if (-1 == ctid){
		perror("clone");
		return -1;
	}


//	syscall(SYS_futex, &sync_clone, FUTEX_WAIT, ctid, NULL, NULL, 0);


	syscall(SYS_tkill, tid, SIGINT);
	syscall(SYS_tkill, tid, SIGINT);

	return 0;
}
