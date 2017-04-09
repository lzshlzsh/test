#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define THREAD_NUM 4
#define PRODUCT_NUM 10

struct Pool{
	pthread_cond_t(cond);
	pthread_mutex_t(mutex);
	int flag;
}g_pool;


static void producer()
{
	if (pthread_mutex_lock(&g_pool.mutex) != 0){
		perror("pthread_mutex_lock");
		exit(errno);
	}
	/*produce*/
	
//	sleep(1);

	g_pool.flag++;

	printf("producer\n");
	
	if (pthread_cond_broadcast(&g_pool.cond) != 0){
		perror("pthread_cond_broadcast");
		exit(errno);
	}
		
	if (pthread_mutex_unlock(&g_pool.mutex) != 0){
		perror("pthread_mutex_lock");
		exit(errno);
	}
}

static void consumer()
{
	if (pthread_mutex_lock(&g_pool.mutex) != 0){
		perror("pthread_mutex_lock");
		exit(errno);
	}
	while (0 == g_pool.flag){
		if (pthread_cond_wait(&g_pool.cond, &g_pool.mutex) != 0){
			perror("pthread_cond_wait");
			exit(errno);
		}
	}
	/*consume*/

	g_pool.flag--;

	printf("consumer\n");

	if (pthread_mutex_unlock(&g_pool.mutex) != 0){
		perror("pthread_mutex_lock");
		exit(errno);
	}
}

static void *child_body(void *arg)
{
	int thr_num = (int)arg;

	if (1 == thr_num % 2){
		consumer();
		return NULL;
	}
	
	producer();

	return NULL;
}

int main()
{
	pthread_t thread[THREAD_NUM - 1];
	int i;

	if (pthread_mutex_init(&g_pool.mutex, NULL) != 0){
		perror("pthread_mutex_init");
		exit(errno);
	}
	
	if (pthread_cond_init(&g_pool.cond, NULL) != 0){
		perror("pthread_cond_init");
		exit(errno);
	}
	
	g_pool.flag = 0;

	for (i = 0; i < THREAD_NUM - 1; i++){
		if (pthread_create(&thread[i], NULL, child_body, (void *)i) != 0){
			perror("pthread_create");
			exit(errno);
		}
	}
	
	consumer();

	for (i = 0; i < THREAD_NUM - 1; i++){
		if (pthread_join(thread[i], NULL) != 0){
			perror("pthread_join");
			exit(errno);
		}
	}

	if (pthread_cond_destroy(&g_pool.cond) != 0){
		perror("pthread_cond_destroy");
		exit(errno);
	}

	if (pthread_mutex_destroy(&g_pool.mutex) != 0){
		perror("pthread_mutex_destroy");
		exit(errno);
	}
	return 0;
}
