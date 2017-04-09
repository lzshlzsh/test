#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	struct addrinfo hints, *res, *result;
	char str[256];

/*	if (argc != 3)
	{
		printf( "usage: %s server service\n", argv[0] );
		exit(1);
	}*/
	bzero(&hints, sizeof(hints));

	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_INET6;
	hints.ai_socktype = 0;

	if (getaddrinfo("ipv6.ustc.edu.cn", 0, &hints, &res)) {
		printf("getaddrinfo failed\n");
		return -1;
	}

	result = res;

	for (; result != NULL; result = result->ai_next)
	{
		void *src;
		printf("\tai_flags: %d\n", result->ai_flags);
		printf("\tai_family: %d\n", result->ai_family);
		printf("\tai_socktype: %d\n", result->ai_socktype);
		printf("\tai_protocol: %d\n", result->ai_protocol);
		printf("\t:ai_addrlen %d\n", result->ai_addrlen);
		printf( "\tai_canonname: %s\n", result->ai_canonname);
		if (AF_INET == result->ai_family) {
			src = &((struct sockaddr_in *)result->ai_addr)->sin_addr; 
		} else {
			src = &((struct sockaddr_in6 *)result->ai_addr)->sin6_addr; 
		}
		inet_ntop(result->ai_family, src, str, sizeof(str));
		printf( "ad_addr: %s\n", str);
		printf( "==========================\n" );
	}

	freeaddrinfo(res);
	return 0;
} 
