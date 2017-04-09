#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <errno.h>
#include <assert.h>
//#include <pthread.h>



#define CSTACKSIZE (4 << 10)
#define DELAY (1 << 20)
#define N 10 

static int *thread_sync;
static int A[N] = {0,};

static int child(void *arg)
{
	struct timeval tv;
	int i;

	for (i = 0; i < N; i++){
		if (gettimeofday(&tv, NULL) < 0){
			perror("gettimeofday");
			exit(errno);
		}
		A[i] = tv.tv_usec % N;
	}

	return 0;
}

int main(int argc, char **argv)
{
	int *ctid;
	int i;
	int **cstack;
	int cthrd_num = 1;
	struct timeval tv;
//	pthread_barrier_t barrier;

	if (argc > 1){
		cthrd_num = atoi(argv[1]);
	}

/*	if (0 != pthread_barrier_init(&barrier, NULL, cthrd_num + 1)){
		perror("pthread_barrier_init");
		exit(errno);
	}*/
	
	for (i = 0; i < cthrd_num; i++){
		thread_sync = malloc(sizeof(thread_sync[0]) * cthrd_num);	
		ctid = malloc(sizeof(ctid[0]) * cthrd_num);
		cstack = malloc(sizeof(cstack[0]) * cthrd_num);
		assert(thread_sync && ctid && cstack);
	}

	for (i = 0; i < cthrd_num; i++){
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

//	pthread_barrier_wait(&barrier);

	for (i = 0; i < N; i++){
		if (gettimeofday(&tv, NULL) < 0){
			perror("gettimeofday");
			exit(errno);
		}
		A[i] = tv.tv_usec % N;
	}


	for (i = 0; i < cthrd_num; i++){
		syscall(SYS_futex, &thread_sync[i], FUTEX_WAIT, ctid[i], NULL, NULL, 0);
	}

	
	for (i = 0; i < N; i++){
		printf("%d\n", A[i]);
	}
		
	return 0;
}




