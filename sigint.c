#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <pthread.h>

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

/*traditional signal handling*/
static void sigint_handler(int num)
{
	printf("SIGINT happened, tid %ld\n", syscall(SYS_gettid));
	if (pthread_mutex_lock(&g_mutex)) {
		perror("handler: pthread_mutex_lock");
	}
	printf("handler: hold lock\n");
	sleep(1);
	struct sigaction act;
	act.sa_flags = SA_ONESHOT | SA_NOMASK;
	act.sa_handler = sigint_handler;
	if(-1 == sigaction(SIGINT, &act, NULL)){
		perror("signal: ");
		exit(-1);
	}
	if (pthread_mutex_unlock(&g_mutex)) {
		perror("handler: pthread_mutex_unlock");
	}
}
int main()
{
	struct sigaction act;
	act.sa_flags = SA_ONESHOT | SA_NOMASK;
	act.sa_handler = sigint_handler;
	printf("main tid: %ld\n", syscall(SYS_gettid));
	if(-1 == sigaction(SIGINT, &act, NULL)){
		perror("signal: ");
		exit(-1);
	}
	while (1){
		if (pthread_mutex_lock(&g_mutex)) {
			perror("main: pthread_mutex_lock");
		}
		printf("main: hold lock\n");
		sleep(5);
		if (pthread_mutex_unlock(&g_mutex)) {
			perror("main: pthread_mutex_unlock");
		}
	}
	return 0;
}
