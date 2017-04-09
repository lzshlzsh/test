#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define THREAD_NUMS 5

void *PrintHello(void *threadid)
{
	sleep(1);
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t threads[THREAD_NUMS];
	int rc=1, t=0;
	void *status;

	printf("In main process: creating thread %d\n", t);
	rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
//	sleep(1);
	if(rc)
	{
		printf("ERROR: return code from pthread_create() is %d\n", rc);
		exit(-1);
	};

	pthread_join(threads[t], &status);
	printf("The parent thread: %d\n", t);

	return 0;
}
