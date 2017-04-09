#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>


#define FIFO "tmp.fifo"

static inline void clr_fl(int fd, int flag)
{
	int fl;

	if ((fl = fcntl(fd, F_GETFL)) < 0){
		perror("fcntl error");
		exit(errno);
	}
	fl &= ~flag;

	if (fcntl(fd, F_SETFL, fl) < 0){
		perror("fcntl error");
		exit(errno);
	}
}

int main()
{
	int fdread, fdwrite;

	unlink(FIFO);

	if (mkfifo(FIFO, S_IRUSR | S_IWUSR) < 0){
		perror("mkfifo error");
		exit(errno);
	}


//	if ((fdread = open(FIFO, O_RDONLY)) < 0){ /*Oops: block forvever*/
	if ((fdread = open(FIFO, O_RDONLY | O_NONBLOCK)) < 0){
		perror("open error");
		exit(errno);
	}

//	if ((fdwrite = open(FIFO, O_WRONLY | O_NONBLOCK)) < 0){ /*not necessary*/
	if ((fdwrite = open(FIFO, O_WRONLY)) < 0){
		perror("open error");
		exit(errno);
	}

	clr_fl(fdwrite, O_NONBLOCK);

	unlink(FIFO);

	return 0;
}
