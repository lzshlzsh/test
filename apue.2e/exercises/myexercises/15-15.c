#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define NLOOPS 1000
#define SIZE sizeof(long)
#define MODE 0666

static int update(long *ptr)
{
	return (*ptr)++;
}

int main()
{
	int i, counter;
	pid_t pid;
	void *area;
	int id;

	if ((id = shmget(IPC_PRIVATE, SIZE, 
			IPC_CREAT | IPC_EXCL | MODE)) < 0){
		err_sys("shmget error");
	}
	
	printf("shmget id = %d\n", id);

	area = shmat(id, NULL, 0);
	if ((void *)-1 == area){
		err_sys("shmat error");
	}

	TELL_WAIT();

	if ((pid = fork()) < 0){
		err_sys("fork error");
	}else if (pid > 0){
		printf("parent: %d\n", pid);
		for (i = 0; i < NLOOPS; i += 2){
			if ((counter = update((long *)area)) != i)
				err_quit("parent: expected %d, got %d", i, counter);
			TELL_CHILD(pid);
			WAIT_CHILD();
		}
		if (shmdt(area) < 0)
			err_sys("parent shmdt error");
	}else {
		printf("child: %d\n", getppid());
		for (i = 1; i < NLOOPS; i += 2){
			WAIT_PARENT();
			if ((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);
			TELL_PARENT(getppid());
		}
		if (shmdt(area) < 0)
			err_sys("child shmdt error");
		exit(0);
	}

	if (shmctl(id, IPC_RMID, NULL) == -1){
		err_sys("shmctl error");
	}

	return 0;
}
