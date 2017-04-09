#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>

using namespace std;

int main(int argc, char **argv)
{
	char *ptr,**pptr;
	struct hostent *hptr;
	char str[32];
	char ipaddr[128];
	struct in_addr *hipaddr = (struct in_addr *)ipaddr;
	int af = AF_INET;

	if (argc < 2) {
		printf("Usage: %s addr [protocol]\n", argv[0]);
		printf("\tprotocol: 0 for ipv4, 1 for ipv6, default ipv4\n");
		return -1;
	} else if (argc >= 3) {
		if (!strcmp("1", argv[2])) {
			af = AF_INET6;
		}
	}
	
	/* 取得命令后第一个参数，即要解析的IP地址 */
	ptr = argv[1];
	/* 调用inet_aton()，ptr就是以字符串存放的地方的指针，hipaddr是in_addr形式的地址 */
	if(!inet_pton(af, ptr, hipaddr))
	{
		printf("inet_aton error\n");
		return 1;
	}
	/* 调用gethostbyaddr()。调用结果都存在hptr中 */
	if ((hptr = gethostbyaddr(hipaddr, AF_INET6 == af ? 16 : 4, af) ) == NULL )
	{
		printf("gethostbyaddr error for addr:%s\n", ptr);
		return 1; /* 如果调用gethostbyaddr发生错误，返回1 */
	}
	/* 将主机的规范名打出来 */
	printf("official hostname:%s\n",hptr->h_name);
	/* 主机可能有多个别名，将所有别名分别打出来 */
	for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
		printf("  alias:%s\n",*pptr);
	/* 根据地址类型，将地址打出来 */
	switch(hptr->h_addrtype)
	{
		case AF_INET:
		case AF_INET6:
			pptr=hptr->h_addr_list;
			/* 将刚才得到的所有地址都打出来。其中调用了inet_ntop()函数 */
			for(;*pptr!=NULL;pptr++)
				printf("  address:%s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
			break;
		default:
			printf("unknown address type\n");
			break;
	}
	return 0;
}
