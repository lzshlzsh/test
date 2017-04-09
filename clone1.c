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


static int child(void *arg)
{
	int tid = syscall(SYS_gettid);

	printf("child thread %d\n", tid);

	return 0;
}


int main()
{
	int ctid, tid;
	int sync_clone;
	char cstack[4 << 10];

	tid = syscall(SYS_gettid);
	printf("parent thread %d\n", tid);

	ctid = clone(child, &cstack[(4 << 10) -1],  SIGCHLD | CLONE_PARENT_SETTID | 
				CLONE_CHILD_CLEARTID, NULL, &sync_clone, 
				NULL, &sync_clone);

	if (-1 == ctid){
		perror("clone");
		return -1;
	}


	//syscall(SYS_futex, &sync_clone, FUTEX_WAIT, ctid, NULL, NULL, 0);


	return 0;
}
