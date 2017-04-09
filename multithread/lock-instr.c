#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */


#define CSTACKSIZE (4 << 10)
#define DELAY (1 << 20)

#define THREADS_NUM 3
#define ITERATION 10000

//static int cstack[CSTACKSIZE] = {0,};
static int thread_sync[THREADS_NUM] = {0, };
static int g_counter = 0;

#define LOCK lock
#define INC_G_COUNTER \
	do {\
		asm volatile( \
		"LOCK incl %0 \n" \
		: "+m"(g_counter)\
		: \
		: "memory" \
		); \
	} while(0)

static int child(void *arg)
{
	int i;
	for (i = 0; i < ITERATION; i++){
		INC_G_COUNTER;
	}
	return 0;
}

int main()
{
	int ctid[THREADS_NUM];
	int i;
	int *cstack[THREADS_NUM];

	for (i = 0; i < THREADS_NUM; i++){
		cstack[i] = malloc(sizeof(int) * CSTACKSIZE);
		if (!cstack[i]){
			printf("malloc error\n");
			exit(1);
		}
		ctid[i] = clone(child, &cstack[i][CSTACKSIZE], CLONE_VM | CLONE_FS | 
				CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD | 
				CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID, (void *)i, 
				&thread_sync[i], NULL, &thread_sync[i]);

		if (-1 == ctid[i]){
			printf("clone error\n");
			exit(1);
		}
	}

	for (i = 0; i < ITERATION; i++){
		INC_G_COUNTER;
	}

	for (i = 0; i < THREADS_NUM; i++){
		syscall(SYS_futex, &thread_sync[i], FUTEX_WAIT, ctid[i], NULL, NULL, 0);
	}

	if ((THREADS_NUM + 1) * ITERATION == g_counter ){
		printf("ok, got %d\n", g_counter);
	}else{
		printf("error, expected %d, got %d\n", (THREADS_NUM + 1) * ITERATION, g_counter);
	}
		
	return 0;
}




