#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    int sock;
//    struct sockaddr_un addr;
//    socklen_t len;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock < 0){
        perror("socket");
        return -1;
    }

    getchar();

    close(sock);
    return 0;
}
