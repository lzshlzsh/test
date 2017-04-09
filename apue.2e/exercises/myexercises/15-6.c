#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{

#if 1	
	FILE *fp;
	if ((fp = popen("/bin/true", "r")) == NULL){
		fprintf(stderr, "popen error\n");
		exit(errno);
	}
	if (system("sleep 3") == -1){
		fprintf(stderr, "system error\n");
		exit(errno);
	}
	if (pclose(fp) == -1){
		fprintf(stderr, "pclose error\n");
		exit(errno);
	}
#else
	pid_t pid1, pid2;
	int rc;
	/*simulate popen*/
	if (!(pid1 = fork())){
		execl("/bin/true", "true", NULL);
		exit(0);
	}
	/*simulate system*/
	if ((pid2 = fork())){
		while ((rc = wait(NULL)) != pid2){
			if (-1 == rc){
				perror("wait 2");
				exit(errno);
			}
		}
	}else{
		sleep(3);
		exit(0);
	}
	/*simulate pclose*/
	if (-1 == wait(NULL)){
		perror("wait 2");
		exit(errno);
	}

#endif
	return 0;
}

