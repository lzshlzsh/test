#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	pid_t cpid;
	int fd[2];
	char buf = 'A';
	int filedes;
	struct flock flk;

	flk.l_type = F_WRLCK;
	flk.l_whence = SEEK_SET;
	flk.l_start = 0;
	flk.l_len = 1;
	flk.l_pid = 0;

	if (pipe(fd) < 0){
		perror("pipe");
		exit(1);
	}

#if 1	
	printf("parent open\n");

	if ((filedes = open("test", O_WRONLY)) < 0){
		perror("open");
		exit(1);
	}
#endif	

	if ((cpid = fork()) < 0){
		perror("fork");
		exit(1);	
	}else if (!cpid){

#if 1	
		printf("child open\n");
		if ((filedes = open("test", O_WRONLY)) < 0){
			perror("open");
			exit(1);
		}

		if (fcntl(filedes, F_GETLK, &flk) < 0){
			perror("fcntl");
			exit(1);
		}

		if (flk.l_pid){
			printf("file is write-locked by %d\n", flk.l_pid);
		}
#endif
		if (!access("test", W_OK)){
			printf("file cannot be written\n");
		}

		if (-1 != fd[1]){
			close(fd[1]);
		}
		if (1 != read(fd[0], &buf, 1) || 'A' != buf){
			fprintf(stderr, "[%d]read error", getpid());
			exit(1);
		}
		exit(0);
	}



	if (-1 != fd[0]){
		close(fd[0]);
	}

	if (1 != write(fd[1], &buf, 1)){
		perror("write");
		exit(1);
	}

	if (wait(NULL) < 0){
		perror("wait");
		exit(1);
	}


	return 0;
}
