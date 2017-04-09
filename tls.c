#define _GNU_SOURCE
#include <sched.h>
#include <sys/types.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <signal.h>
#include <linux/unistd.h>

__thread int my_tls = 0;

static int child(void *arg)
{
	fprintf(stderr, "%ld: %p\n", syscall(SYS_gettid), &my_tls);	
	return 0;
}


int main()
{
	pthread_t ctid[10];
	int tid;
	int sync_clone[10];
	int cstack[10][4 << 10];
	int i;
	void *retval;

	tid = syscall(SYS_gettid);
	printf("parent thread %d\n", tid);

	for (i = 0; i < 10; i++){
		/*ctid[i] = clone(child, &cstack[i][(4 << 10) -1], CLONE_FILES | SIGCHLD |
					CLONE_FS | CLONE_SIGHAND | CLONE_VM | CLONE_PARENT_SETTID | 
					CLONE_CHILD_CLEARTID | CLONE_THREAD, NULL, &sync_clone[i], 
					NULL, &sync_clone[i]);*/
			
//		if (-1 == ctid[i]){
		if (0 != pthread_create(&ctid[i], NULL, child, NULL)){
			perror("clone");
			syscall(SYS_exit_group, -1);
		}
	}

	for (i = 0; i < 10; i++){
//		syscall(SYS_futex, &sync_clone[i], FUTEX_WAIT, ctid[i], NULL, NULL, 0);
		pthread_join(ctid[i], &retval);
	}


	return 0;
}
