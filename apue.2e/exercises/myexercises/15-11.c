#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct msgbuf {
	long mtype;       /* message type, must be > 0 */
	char mtext[128];    /* message data */
};

#define mode 0606
#define N 50

int main(int argc, char **argv)
{
	int fd;
	struct msgbuf msg;
	int i;
	
	if (argc > 2){
		fprintf(stderr, "usage: %s [-r]\n", argv[0]);
		exit(1);
	}

	if (2 == argc){
		fd = atoi(argv[1]);
		for (i = 0; i < N; i++){
			if (msgrcv(fd, &msg, sizeof(msg), 0, IPC_NOWAIT) != sizeof(msg)){
				perror("msgrcv");
				exit(0);
			}
			printf("received msg form %d: %s", fd, msg.mtext);
		}
		if (msgctl(fd, IPC_RMID, NULL) < 0){
			perror("msgctl");
			exit(errno);
		}
	}else{
		fd = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | mode);
		if (fd < 0){
			perror("msgget");
			exit(errno);
		}

		printf("msg id = %d\n", fd);

		msg.mtype = 1;
		sprintf(msg.mtext, "%s\n", "hello world!");


		for (i = 0; i < N; i++){
			if (msgsnd(fd, &msg, sizeof(msg), 0) < 0){
				perror("msgsnd");
				exit(errno);
			}
		}
	}
	return 0;
}
