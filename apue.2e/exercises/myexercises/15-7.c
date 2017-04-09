/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
	int fd[2];

	if (-1 == pipe(fd)){
		perror("pipe2");
		exit(errno);
	}
	
#if 0	
	fd_set fs;
#if 0	
	close(fd[1]);
	FD_ZERO(&fs);
	FD_SET(fd[0], &fs);
	if (-1 == select(1, &fs, NULL, NULL, NULL)){
		perror("select error");
		exit(errno);
	}
	if (FD_ISSET(fd[0], &fs)){
		printf("select: fd[0] in fs\n");
	}else{
		printf("select: fd[0] NOT in fs\n");
	}
#else
	close(fd[0]);
	FD_ZERO(&fs);
	FD_SET(fd[1], &fs);
	if (-1 == select(1, NULL, &fs, NULL, NULL)){
		perror("select error");
		exit(errno);
	}
	if (FD_ISSET(fd[0], &fs)){
		printf("select: fd[1] in fs\n");
	}else{
		printf("select: fd[1] NOT in fs\n");
	}
#endif
#else
	struct pollfd fds;
	int idx;
#if 0
	close(fd[1]);
	fds.fd =  fd[0];
	fds.events = POLLIN;
	
	if (-1 == (idx = poll(&fds, 1, -1))){
		perror("poll error");
		exit(errno);
	}
	printf("poll: returned event, %d\n", fds.revents);
#else
	close(fd[0]);
	fds.fd =  fd[1];
	fds.events = POLLOUT;
	
	if (-1 == (idx = poll(&fds, 1, -1))){
		perror("poll error");
		exit(errno);
	}
	printf("poll: returned event, %d\n", fds.revents);
#endif
#endif

	return 0;
}
