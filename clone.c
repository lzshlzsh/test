#define _GNU_SOURCE
#include <sched.h>
#include <sys/types.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <signal.h>
#include <sys/times.h>
#include <time.h>



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
	struct tms tms;
	long clk_tck = sysconf(_SC_CLK_TCK);
//	int i;
	printf("child thread %d\n", tid);

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = csig_handler;
	sigaction(SIGINT, &act, NULL);


	syscall(SYS_tkill, tid, SIGINT);
	syscall(SYS_tkill, tid, SIGINT);
	
//	for (i = 0; i < (1 << 30); i++);

	times(&tms);
	printf("[%d] usr: %f, sys: %f, clock: %f\n", tid, (float)tms.tms_utime / clk_tck, 
					(float)tms.tms_stime / clk_tck, 
					(float)clock() / CLOCKS_PER_SEC);
	return 0;
}


int main()
{
	int ctid, tid;
	int sync_clone;
	char cstack[4 << 10];
	struct tms tms;
	long clk_tck = sysconf(_SC_CLK_TCK);

	tid = syscall(SYS_gettid);
	printf("parent thread %d\n", tid);

	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = psig_handler;
	sigaction(SIGINT, &act, NULL);

	syscall(SYS_tkill, tid, SIGINT);

	ctid = clone(child, &cstack[(4 << 10)], CLONE_FILES | SIGCHLD |
				CLONE_FS /*| CLONE_SIGHAND*/ | CLONE_VM | CLONE_PARENT_SETTID | 
				CLONE_CHILD_CLEARTID /*| CLONE_THREAD*/, NULL, &sync_clone, 
				NULL, &sync_clone);

	if (-1 == ctid){
		perror("clone");
		return -1;
	}


	syscall(SYS_futex, &sync_clone, FUTEX_WAIT, ctid, NULL, NULL, 0);



	syscall(SYS_tkill, tid, SIGINT);
	syscall(SYS_tkill, tid, SIGINT);

	times(&tms);
	printf("[%d] usr: %f, sys: %f, clock: %f\n", tid, (float)tms.tms_utime / clk_tck, 
					(float)tms.tms_stime / clk_tck, 
					(float)clock() / CLOCKS_PER_SEC);
	return 0;
}
