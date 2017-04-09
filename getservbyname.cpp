#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct servent *serv;
	const char *proto = NULL;

	if (argc < 2) {
		printf("Incorrect parameters. Usage:\n");
		printf("\t%s service-name [protocol-name]\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (argc >= 3) {
		proto = argv[2];
	}
	/* getservbyname() - 打开 etc/services 文件并返回所需的服务及协议信息 */
	serv = getservbyname(argv[1], proto);
	if (serv == NULL) {
		printf("Service \"%s\" not found for protocol \"%s\"\n", argv[1], argv[2]);
		return EXIT_FAILURE;
	}

	/* Print it. */
	printf("Name: %-15s  Port: %5d    Protocol: %-6s\n",
			serv->s_name,ntohs(serv->s_port),serv->s_proto);
	for (char **s = serv->s_aliases; *s; s++) {
		printf("alias: %s\n", *s);
	}
	return EXIT_SUCCESS;
}
