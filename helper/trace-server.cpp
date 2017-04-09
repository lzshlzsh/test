#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

#define BACKLOGLEN 5
#define RECVBUFSIZE ((1 << 20) * 8)

static char wrf_pc_buf[RECVBUFSIZE];

static void do_receive(int cfd, const char *host, const char *service);

static void usage(const char *filename)
{
	fprintf(stderr, "Usage: %s port\n", filename);	
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	int fd = -1; /*avoid warning*/
	struct addrinfo hints;
	struct addrinfo *res, *ai;
	int ret;
	char host[NI_MAXHOST], service[NI_MAXSERV];
	int cfd; /*connection fd*/
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;

	
	if (2 != argc){
		usage(argv[0]);
	}

	memset(&hints, 0, sizeof(hints));	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_PASSIVE;

	ret = getaddrinfo(NULL, argv[1], &hints, &res);
	if (0 != ret){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
		exit(EXIT_FAILURE);
	}

	for (ai = res; ai; ai = ai->ai_next){
		fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		if (-1 == fd){
			continue;
		}

		if (0 == bind(fd, ai->ai_addr, ai->ai_addrlen)){
			if (getnameinfo(ai->ai_addr, ai->ai_addrlen, host, NI_MAXHOST, 
						service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV)){
				perror("getnameinfo:");
				exit(EXIT_FAILURE);
			}
			printf("server bind on %s:%s\n", host, service);
			break;
		}
		close(fd);
	}

	if (NULL == ai){
		fprintf(stderr, "cannot bind\n");
		usage(argv[0]);
	}

	freeaddrinfo(res);

	if (listen(fd, BACKLOGLEN) < 0){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	for (; ;){
		peer_addr_len = sizeof(struct sockaddr_storage);
		if ((cfd = accept(fd, (struct sockaddr *)&peer_addr, &peer_addr_len)) < 0){
			perror("accept");
			exit(EXIT_FAILURE);
		}
		if (getnameinfo((struct sockaddr *)&peer_addr, peer_addr_len, host, NI_MAXHOST, 
					service, NI_MAXSERV, 0)){
			perror("getnameinfo:");
			exit(EXIT_FAILURE);
		}
		do_receive(cfd, host, service);
		close(cfd);
	}

	close(fd);

	return 0;
}


static void do_receive(int cfd, const char *host, const char *service)
{

	string filename = host;	
	char sufix[16];
	int ret;
	int fd;
	int size;

	printf("receive from %s:%s\n", host, service);	

	filename += service;

	for (unsigned int i = 0; true; i++){
		sprintf(sufix, ".%x", i);

		for (size = 0; size < RECVBUFSIZE; size += ret){
			if ((ret = read(cfd, wrf_pc_buf + size, RECVBUFSIZE - size)) < 0){
				fprintf(stderr, "read");
				exit(EXIT_FAILURE);
			}else if (0 == ret){
				break;
			}
		}

		if (0 == size){
			break;
		}

		printf("write log %s\n", (filename + sufix).c_str());
		fd = open((filename + sufix).c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		if (fd < 0){
			perror("open");
			exit(EXIT_FAILURE);
		}

		if (size != write(fd, wrf_pc_buf, size)){
			perror("write");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}

}
