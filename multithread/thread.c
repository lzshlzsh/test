#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */




#define CSTACKSIZE (4 << 10)
#define DELAY (1 << 20)
#define N 4
#define THREADS_NUM 1

//static int cstack[CSTACKSIZE] = {0,};
static int thread_sync[THREADS_NUM] = {0, };
static int A[N] = {0,};
static struct timespec ts = {0, 20000000};
static  int my_sync = 0;

static int child(void *arg)
{

	int i;
	for (i = 0; i < N; i++){
		A[i] = N * ((int)arg + 1) + i;
//		syscall(SYS_nanosleep, &ts, NULL);
	}

	syscall(SYS_futex, &my_sync, FUTEX_WAKE, 1, NULL, NULL, 0);
	my_sync = 1;

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

	syscall(SYS_futex, &my_sync, FUTEX_WAIT, 0, NULL, NULL, 0);

	for (i = 0; i < N; i++){
		A[i] = i;
//		syscall(SYS_nanosleep, &ts, NULL);
	}

	for (i = 0; i < THREADS_NUM; i++){
		syscall(SYS_futex, &thread_sync[i], FUTEX_WAIT, ctid[i], NULL, NULL, 0);
	}

	
	for (i = 0; i < N; i++){
		printf("%d\n", A[i]);
	}
		
	return 0;
}




