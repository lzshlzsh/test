#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dlfcn.h>
#include <gnu/lib-names.h>

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

  void *dlhandler = dlopen(LIBM_SO, RTLD_LAZY);
  if (!dlhandler) {
    fprintf(stderr, "dlopen: %s\n", dlerror());
    return -__LINE__;
  }
  dlclose(dlhandler);

    return 0;
}
