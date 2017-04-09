#include "apue.h"

static void	sig_pipe(int);		/* our signal handler */

int
main(void)
{
	int		fd1[2], fd2[2];
	pid_t	pid;
	char	line[MAXLINE];
	FILE *file1, *file2;

	if (signal(SIGPIPE, sig_pipe) == SIG_ERR)
		err_sys("signal error");

	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		err_sys("pipe error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {							/* parent */
		close(fd1[0]);
		close(fd2[1]);
#if 1
		file1 = fdopen(fd1[1], "w");
		if (NULL == file1)
			err_sys("fdopen error");
		file2 = fdopen(fd2[0], "r");
		if (NULL == file2)
			err_sys("fdopen error");
		setbuf(file1, NULL);
		setbuf(file2, NULL);
		while (fgets(line, MAXLINE, stdin) != NULL) {
			if (EOF == fputs(line, file1))
				err_sys("fputs error");
			if (NULL == fgets(line, MAXLINE, file2))
				err_sys("fgets error");
			if (fputs(line, stdout) == EOF)
				err_sys("fputs error");
		}
#else
		while (fgets(line, MAXLINE, stdin) != NULL) {
			n = strlen(line);
			if (write(fd1[1], line, n) != n)
				err_sys("write error to pipe");
			if ((n = read(fd2[0], line, MAXLINE)) < 0)
				err_sys("read error from pipe");
			if (n == 0) {
				err_msg("child closed pipe");
				break;
			}
			line[n] = 0;	/* null terminate */
			if (fputs(line, stdout) == EOF)
				err_sys("fputs error");
		}
#endif
		if (ferror(stdin))
			err_sys("fgets error on stdin");
		exit(0);
	} else {									/* child */
		close(fd1[1]);
		close(fd2[0]);
		if (fd1[0] != STDIN_FILENO) {
			if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd1[0]);
		}

		if (fd2[1] != STDOUT_FILENO) {
			if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
				err_sys("dup2 error to stdout");
			close(fd2[1]);
		}
		if (execl("./add2", "add2", (char *)0) < 0)
			err_sys("execl error");
	}
	exit(0);
}

static void
sig_pipe(int signo)
{
	printf("SIGPIPE caught\n");
	exit(1);
}