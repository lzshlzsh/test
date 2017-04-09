#include<iostream>
#include<signal.h>
#include<unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void SigHandler(int signo,siginfo_t *info,void *context)
{
	char *pMsg=(char*)info->si_value.sival_ptr;
	cout << "Recv Msg:" << (long)pMsg << endl;
}

int main()
{
	struct sigaction sigAct;
	sigAct.sa_flags=SA_SIGINFO;
	sigAct.sa_sigaction=SigHandler;
	pid_t pid_chld;

	if(sigaction(SIGUSR1,&sigAct,NULL) == -1)	{
		perror("set sig_handler");
		exit(1);
	}

	if ((pid_chld = fork())){
		//parent
	}else{
		//child	
		sleep(2);
		exit(0);
	}
	sigval_t val;
	char pMsg[] = "I still believe";
	val.sival_ptr=pMsg;

	if(sigqueue(pid_chld, SIGUSR1,val) == -1){
		perror("sigqueue");
		exit(2);
	}
//	sleep(3);
	return 0;
}
