#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define THREAD_NUM 8
#define N 5

struct bars_struct{
	pthread_barrier_t(barrier);
}*bars;

static int global_array[N];


static void do_write_global()
{
	int i;
	struct timeval tv;

	for (i = 0; i < N; i++){
		if (gettimeofday(&tv, NULL) < 0){
			perror("gettimeofday");
			exit(errno);
		}
		global_array[i] = tv.tv_usec % N;
	}
}

static void write_global()
{
	do_write_global();
	pthread_barrier_wait(&bars->barrier);
#if 1
	do_write_global();
	pthread_barrier_wait(&bars->barrier);
	do_write_global();
	pthread_barrier_wait(&bars->barrier);
	do_write_global();
	pthread_barrier_wait(&bars->barrier);
	do_write_global();
	pthread_barrier_wait(&bars->barrier);
	do_write_global();
	pthread_barrier_wait(&bars->barrier);
#endif
}

static void *child_body(void *arg)
{
	
	write_global();

	return NULL;
}

int main()
{
	int i;
	pthread_t thread[THREAD_NUM - 1];

	bars = (struct bars_struct *)valloc(sizeof(struct bars_struct));

	assert(bars);

//	printf("bars = %p\n", bars);

	if (0 != pthread_barrier_init(&bars->barrier, NULL, THREAD_NUM)){
		perror("pthread_barrier_init");
		exit(errno);
	}


	for (i = 0; i < THREAD_NUM - 1; i++){
		if (0 != pthread_create(&thread[i], NULL, child_body, NULL)){
			perror("pthread_create");
			exit(errno);
		}
	}

	write_global();

//	sleep(2);

	for (i = 0; i < THREAD_NUM - 1; i++){
		if (0 != pthread_join(thread[i], NULL)){
			perror("pthread_join");
			exit(errno);
		}
	}

	for (i = 0; i < N; i++){
		printf("%d\t", global_array[i]);
	}
	printf("\n");

	return 0;
}
