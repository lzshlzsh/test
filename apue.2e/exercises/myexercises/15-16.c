#include <fcntl.h>
#include "apue.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NLOOPS 1000
#define SIZE sizeof(long)
#define MODE 0666

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
								(Linux-specific) */
};


static int g_semid;

void TELL_WAIT()
{
	struct semid_ds sem_ds;
	union semun sem;
	sem.buf = &sem_ds;

	g_semid = semget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | MODE);	
	if (g_semid < 0)
		err_sys("semget error");

	/*initial value*/
	sem.val = 0;
	if (semctl(g_semid, 0, SETVAL, sem) < 0)
		err_sys("semctl 2 error");
	if (semctl(g_semid, 1, SETVAL, sem) < 0)
		err_sys("semctl 3 error");
}
void TELL_PARENT(pid_t pid)
{
	struct sembuf sops;
	sops.sem_num = 1;
	sops.sem_op = 1;
	sops.sem_flg = SEM_UNDO;
	if (semop(g_semid, &sops, 1) < 0)	
		err_sys("semop error");
}
void TELL_CHILD(pid_t pid)
{
	struct sembuf sops;
	sops.sem_num = 0;
	sops.sem_op = 1;
	sops.sem_flg = SEM_UNDO;
	if (semop(g_semid, &sops, 1) < 0)	
		err_sys("semop error");
}

void WAIT_PARENT()
{
	struct sembuf sops;
	sops.sem_num = 0;
	sops.sem_op = -1;
	sops.sem_flg = SEM_UNDO;
	if (semop(g_semid, &sops, 1) < 0)	
		err_sys("semop error");
}
void WAIT_CHILD()
{
	struct sembuf sops;
	sops.sem_num = 1;
	sops.sem_op = -1;
	sops.sem_flg = SEM_UNDO;
	if (semop(g_semid, &sops, 1) < 0)	
		err_sys("semop error");
}

static void TELL_END()
{
	if (semctl(g_semid, 0, IPC_RMID) < 0)
		err_sys("semctl 4 error");
}

static int update(long *ptr)
{
	return (*ptr)++;
}

int main()
{
	int i, counter;
	pid_t pid;
	void *area;

#if 0	
	int fd;
	if ((fd = open("/dev/zero", O_RDWR)) < 0)
		err_sys("open error");
	if (MAP_FAILED == (area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, 
					fd, 0))){
		err_sys("mmap error");
	}
	close(fd);
#else
	if (MAP_FAILED == (area = mmap(0, SIZE, PROT_READ | PROT_WRITE, 
					MAP_ANONYMOUS | MAP_SHARED, -1, 0))){
		err_sys("mmap error");
	}
#endif

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
	}else {
		printf("child: %d\n", getppid());
		for (i = 1; i < NLOOPS; i += 2){
			WAIT_PARENT();
			if ((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);
			TELL_PARENT(getppid());
		}
		exit(0);
	}

	TELL_END();
	return 0;
}
