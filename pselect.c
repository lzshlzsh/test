#include        <time.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <signal.h>
#include        <unistd.h>
#include        <sys/select.h>

#define BUFFSIZE 80

void sig_int(int signo);
void err_sys(const char *p_error);

int
main(int argc, char **argv)
{
        int             maxfdp1;
        fd_set          rset;
        sigset_t        sigmask;
        ssize_t         nread;
        char            buf[BUFFSIZE];
        struct sigaction act;

        /* set SIGINT signal handler */
        act.sa_handler = sig_int;
        if (sigemptyset(&act.sa_mask) == -1)
                err_sys("sigemtpyset error");
        act.sa_flags = 0;
       
        if (sigaction(SIGINT, &act, NULL) == -1)
                err_sys("sigaction error");
       
        /* initialize read set and add STDIN_FILENO into it */
        FD_ZERO(&rset);
        FD_SET(STDIN_FILENO, &rset);
       
        /* initialize sigmask set and add SIGINT into it */
        if (sigemptyset(&sigmask) == -1)
                err_sys("sigemptyset error");
        if (sigaddset(&sigmask, SIGINT) == -1)
                err_sys("sigaddset error");
       
        /* call pselect() function, always block until STDIN_FILENO readable */
        maxfdp1 = STDIN_FILENO + 1;
        if (pselect(maxfdp1, &rset, NULL, NULL, NULL, &sigmask) <= 0)
                err_sys("pselect error");

        if (FD_ISSET(STDIN_FILENO, &rset)) {
                if ((nread = read(STDIN_FILENO, buf, BUFFSIZE)) == -1)
                        err_sys("read error");
                if (write(STDOUT_FILENO, buf, nread) != nread)
                        err_sys("write error");
        }

        exit(0);
}

void
sig_int(int signo)
{
        char    s[] = "received";

        psignal(signo, s);

        return;
}

void
err_sys(const char *p_error)
{
        perror(p_error);

        exit(1);
}

