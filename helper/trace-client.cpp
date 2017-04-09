#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


#define WRF_PC_BUF_SIZE (1 << 20)
#define WRITE_ITERATION 10

static unsigned int wrf_pc_buf[WRF_PC_BUF_SIZE] = {0x805787, 0x878, };


static void usage(const char *file)
{
	fprintf(stderr, "Usage: %s host port\n", file);
	exit(EXIT_FAILURE);
}


int main(int argc, char **argv)
{
	int fd = -1;
	struct addrinfo hints, *res, *ai;
	int ret;
	char host[NI_MAXHOST], service[NI_MAXSERV];

	if (3 != argc)
		usage(argv[0]);

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_ADDRCONFIG;

	ret = getaddrinfo(argv[1], argv[2], &hints, &res);
	if (0 != ret){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
		exit(EXIT_FAILURE);
	}

	for (ai = res; ai; ai = ai->ai_next){
		fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		if (-1 == fd){
			continue;
		}

		if (0 == connect(fd, ai->ai_addr, ai->ai_addrlen)){
			if (getnameinfo(ai->ai_addr, ai->ai_addrlen, host, NI_MAXHOST, 
						service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV)){
				perror("getnameinfo:");
				exit(EXIT_FAILURE);
			}
			printf("SUCCESS: connect server %s:%s\n", host, service);

			break;
		}
		close(fd);
	}

	if (NULL == ai){
		fprintf(stderr, "cannot connect to server\n");
		usage(argv[0]);
	}

	for (int i = 0; i < WRITE_ITERATION; i++){
		if ((WRF_PC_BUF_SIZE * sizeof(wrf_pc_buf[0])) != 
				write(fd, wrf_pc_buf, WRF_PC_BUF_SIZE * sizeof(wrf_pc_buf[0]))){
			perror("write");
			exit(EXIT_FAILURE);
		}
	}

	close(fd);
	return 0;
}
