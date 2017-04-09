/**
 * @file fork2.cpp
 * @brief
 * @version 1.0
 * @date 02/26/2016 10:11:07 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/wait.h>


void sigint_handler(int signum, siginfo_t *info, void *uc)
{
	printf("[%d]%s received\n", getpid(), strsignal(signum));
}

int main()
{
	struct sigaction act;
	act.sa_sigaction = sigint_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	if (sigaction(SIGINT, &act, NULL) < 0){
		perror("sigaction");
		exit(1);
	}
    for (int i = 0; i < 10; ++i) {
        if (!fork()){
            if (prctl(PR_SET_PDEATHSIG, SIGKILL) < 0) {
                perror("prctl");
                exit(1);
            }
            exit(-120);
            while (1){
                printf("%d\n", getpid());
                sleep(1);
            }
            exit(0);
        }
        int status;
        if (waitpid(-1, &status, 0) > 0) {
            printf("[%d]%d\n", getpid(), static_cast<int8_t>(WEXITSTATUS(status)));
        }
    }
    exit(0);
	while(1) {
        printf("%d\n", getpid());
        sleep(1);
    }
	return 0;
}
