#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define TMPLEN 8192

int main(int argc, char **argv)
{
	char *host;               /* input DNS domain name */
	struct hostent hbuf, *hp; /* output DNS host entry */
	char tmp[TMPLEN];         /* temporary scratch buffer */
	int my_h_errno, rc;       /* DNS error code and return code */
	char **pptr;
	char str[256];

	if (argc != 2) { 
		fprintf(stderr, "usage: %s <hostname>\n", argv[0]);
		exit(0);
	}
	host = argv[1];

	rc = gethostbyname_r(host, &hbuf, tmp, TMPLEN, &hp, &my_h_errno);
	if (rc != 0) {
		printf("gethostbyname_r error: %s\n", hstrerror(my_h_errno));
		exit(0);
	}
	if (&hbuf == hp) {
		printf("ret == *result\n");
	}
	printf("official hostname: %s\n", hp->h_name);
	/* 主机可能有多个别名，将所有别名分别打出来 */
	for(pptr = hp->h_aliases; *pptr != NULL; pptr++)
		printf("alias:%s\n",*pptr);

	printf("h_length: %d\n", hp->h_length);
	printf("h_addrtype: %d\n", hp->h_addrtype);

	/* 根据地址类型，将地址打出来 */
	switch(hp->h_addrtype)
	{
		case AF_INET:
		case AF_INET6:
			pptr=hp->h_addr_list;
			/* 将刚才得到的所有地址都打出来。其中调用了inet_ntop()函数 */
			for(;*pptr!=NULL;pptr++)
				printf("address:%s\n", inet_ntop(hp->h_addrtype, *pptr, str, sizeof(str)));
			break;
		default:
			printf("unknown address type\n");
			break;
	}
	return 0;
}

