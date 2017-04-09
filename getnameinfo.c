#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>


int main()
{
	struct sockaddr *sa;    /* input */
	socklen_t len;         /* input */
	char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

	if (getnameinfo(sa, len, hbuf, sizeof(hbuf), sbuf,
				sizeof(sbuf), NI_NUMERICHOST | NI_NUMERICSERV) == 0)
		printf("host=%s, serv=%s\n", hbuf, sbuf);


	if (getnameinfo(sa, len, hbuf, sizeof(hbuf),
				NULL, 0, NI_NAMEREQD))
		printf("could not resolve hostname\n");
	else
		printf("host=%s\n", hbuf);

	return 0;
}

