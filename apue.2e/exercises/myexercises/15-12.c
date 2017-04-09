#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

struct msgbuf {
	long mtype;       /* message type, must be > 0 */
	char mtext[128];    /* message data */
};

#define mode 0666
#define N 5

int main(int argc, char **argv)
{
	int fd[5];
	struct msgbuf msg;
	int i;
	key_t key;


	for (i = 0; i < N; i++){
		key = ftok(argv[0], i + 1);
		if (key < 0){
			perror("ftok");
			exit(errno);
		}
		fd[i] = msgget(key, IPC_CREAT | IPC_EXCL | mode);
		if (fd[i] < 0){
			perror("msgget");
			exit(errno);
		}
		printf("%d: %d\n", i + 1, fd[i]);
	}
	for (i = 0; i < N; i++){
		if (msgctl(fd[i], IPC_RMID, NULL) < 0){
			perror("msgctl");
			exit(errno);
		}
	}

	for (i = 0; i < N; i++){
		fd[i] = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | mode);
		if (fd[i] < 0){
			perror("msgget");
			exit(errno);
		}
		msg.mtype = 1;
		sprintf(msg.mtext, "%s\n", "hello world!");
		if (msgsnd(fd[i], &msg, sizeof(msg), 0) < 0){
			perror("msgsnd");
			exit(errno);
		}
	}

	return 0;
}
