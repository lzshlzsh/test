#include <sys/types.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <sched.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/syscall.h> 

#define THREAD_STACK_SIZE (2 * getpagesize())

int g_futex_addr = 0;
int g_sync;

static int child_body(void *arg)
{
	int ret;
	do {
		ret = syscall(SYS_futex, &g_futex_addr, FUTEX_WAIT_PRIVATE, 0, NULL);

		if (ret < 0){
			printf("[%ld]\n", syscall(SYS_gettid));
			perror("syscall futex child 1");
		}
		printf("[%ld] ret = %d, g_futex_addr = %d\n", syscall(SYS_gettid), ret, g_futex_addr);
	}while (0/* == g_futex_addr*/);

	return 0;
}

static void futex_wake_noclear(int *addr)
{
#if 0	
	if (syscall(SYS_futex, addr, FUTEX_WAKE_PRIVATE, 1) < 0){
		printf("[%ld]\n", syscall(SYS_gettid));
		perror("syscall futex_wake_noclear");
		exit(errno);
	}
#else
	*addr = 1;
#endif
}


int main()
{
	char child_stack[THREAD_STACK_SIZE];
	int child_tid;

	child_tid = clone(child_body, &child_stack[THREAD_STACK_SIZE], 
			CLONE_CHILD_CLEARTID | CLONE_FILES | CLONE_FS | 
			CLONE_PARENT_SETTID | CLONE_SIGHAND | 
			CLONE_THREAD | CLONE_VM, NULL, &g_sync, NULL, &g_sync);


	if (child_tid < 0){
		perror("clone");
		exit(errno);
	}


	sleep(1);

	futex_wake_noclear(&g_futex_addr);
	futex_wake_noclear(&g_futex_addr);

	sleep(1);
	
	if (syscall(SYS_futex, &g_sync, FUTEX_WAIT, child_tid, NULL)
			< 0){
		printf("[%ld]\n", syscall(SYS_gettid));
		perror("syscall futex main, maybe child has exited");
	}

	return 0;
}

