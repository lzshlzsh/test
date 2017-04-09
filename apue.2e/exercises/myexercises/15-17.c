#include <fcntl.h>
#include "apue.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <string.h>


#define NLOOPS 8
#define SIZE sizeof(long)
#define MODE 0666
#define NAME_SIZE 64

static int g_fd;
static char g_name[NAME_SIZE];

void TELL_WAIT()
{
	snprintf(g_name, NAME_SIZE, "%d", getpid());

	g_fd = open(g_name, O_WRONLY | O_CREAT);
	if (g_fd < 0)
		err_sys("open error");

}
static void PREPARE_PARENT()
{
	struct flock flock;

	flock.l_type = F_WRLCK;
	flock.l_whence = SEEK_SET;
	flock.l_start = 0;
	flock.l_len = 1;

	if (fcntl(g_fd, F_SETLK, &flock) < 0)
		err_sys("fcntl error");
}
static void PREPARE_CHILD()
{
	struct flock flock;

	flock.l_type = F_WRLCK;
	flock.l_whence = SEEK_SET;
	flock.l_start = 1;
	flock.l_len = 1;

	if (fcntl(g_fd, F_SETLK, &flock) < 0)
		err_sys("fcntl error");
}
void TELL_PARENT(pid_t pid)
{
	static int i = 1;
	struct flock flock;
	flock.l_type = F_UNLCK;
	flock.l_whence = SEEK_SET;
	flock.l_start = i++;
	flock.l_len = 1;

	i = i % 2;
	
	if (fcntl(g_fd, F_SETLK, &flock) < 0)
		err_sys("fcntl error");
}
void TELL_CHILD(pid_t pid)
{
	static int i = 0;
	struct flock flock;
	flock.l_type = F_UNLCK;
	flock.l_whence = SEEK_SET;
	flock.l_start = i++;
	flock.l_len = 1;
	
	i = i % 2;

	if (fcntl(g_fd, F_SETLK, &flock) < 0)
		err_sys("fcntl error");
}

void WAIT_PARENT()
{
	static int i = 0;
	struct flock flock;
	flock.l_type = F_WRLCK;
	flock.l_whence = SEEK_SET;
	flock.l_start = i++;
	flock.l_len = 1;

	i = i % 2;
	
	if (fcntl(g_fd, F_SETLKW, &flock) < 0)
		err_sys("fcntl error");
}
void WAIT_CHILD()
{
	static int i = 1;
	struct flock flock;
	flock.l_type = F_WRLCK;
	flock.l_whence = SEEK_SET;
	flock.l_start = i++;
	flock.l_len = 1;
	
	i = i % 2;

	if (fcntl(g_fd, F_SETLKW, &flock) < 0)
		err_sys("fcntl error");
}

static void TELL_END()
{
	if (unlink(g_name) < 0)
		err_sys("unlink error");
}

static int update(long *ptr)
{
	return (*ptr)++;
}

int main()
{
	int i, counter;
	pid_t pid, ppid;
	void *area;
	int fd1[2], fd2[2];
	char c;

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

	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		err_sys("pipe erro");

	ppid = getpid();

	TELL_WAIT();

	if ((pid = fork()) < 0){
		err_sys("fork error");
	}else if (pid > 0){
		printf("parent: %d\n", ppid);


		PREPARE_PARENT();

		close(fd1[1]);
		close(fd2[0]);

		if (read(fd1[0], &c, 1) != 1)
			err_sys("read erro");
		if (write(fd2[1], "p", 1) != 1)
			err_sys("write erro");


		if ('c' != c){
			printf("parent: %c received\n", c);
			exit(-1);
		}

		for (i = 0; i < NLOOPS; i += 2){
			if ((counter = update((long *)area)) != i)
				err_quit("parent: expected %d, got %d", i, counter);
			else
				printf("%d: %d\n", ppid, counter);
			TELL_CHILD(pid);
			WAIT_CHILD();
		}

		close(fd1[0]);
		close(fd2[1]);
	}else {
		pid = getpid();
		printf("child: %d\n", pid);
	
		close(fd1[0]);
		close(fd2[1]);

		PREPARE_CHILD();

		if (write(fd1[1], "c", 1) != 1)
			err_sys("write error");
		if (read(fd2[0], &c, 1) != 1)
			err_sys("read erro");
		if ('p' != c){
			printf("parent: %c received\n", c);
			exit(-1);
		}

		for (i = 1; i < NLOOPS; i += 2){
			WAIT_PARENT();
			if ((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);
			else
				printf("%d: %d\n", pid, counter);
			TELL_PARENT(ppid);
		}

		close(fd1[1]);
		close(fd2[0]);
		exit(0);
	}

	TELL_END();
	return 0;
}
