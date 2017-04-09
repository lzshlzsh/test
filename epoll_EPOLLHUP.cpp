/**
 * @file epoll_EPOLLHUP.cpp
 * @brief
 * @version 1.0
 * @date 02/13/2017 02:59:09 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
 */

#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief
 * @param[in] argc
 * @param[in] argv
 * @return 0 if success, < 0 otherwise
 */
int main(int argc, char **argv) {
    int pipefd[2] = {-1, -1};
    int epfd = -1;
    struct epoll_event event;
    int err;
    char buf[256] = "shit";
    int err_cnt = 0;

    err = pipe(pipefd);
    if (err < 0) {
        fprintf(stderr, "pipe: %s\n", strerror(errno));
        goto __ret;
    }

    err =  fork();
    if (err < 0) {
        fprintf(stderr, "fork: %s\n", strerror(errno));
        goto __ret;
    } else if (0 == err) {
        close(pipefd[0]);
        sleep(3);
        exit(0);
    }
    close(pipefd[1]);

    epfd = epoll_create(1);
    if (epfd < 0) {
        fprintf(stderr, "epoll_create: %s\n", strerror(errno));
        err = -2;
        goto __ret;
    }

    event.events = EPOLLIN;
    event.data.fd = pipefd[0];

    err = epoll_ctl(epfd, EPOLL_CTL_ADD, pipefd[0], &event);
    if (err < 0) {
        fprintf(stderr, "epoll_ctl: %s\n", strerror(errno));
        err = -3;
        goto __ret;
    }

    while (true) {
        err = epoll_wait(epfd, &event, 1, 1000);
        if (err < 0) {
            fprintf(stderr, "epoll_wait: %s\n", strerror(errno));
            sleep(1);
        } else if (0 == err) {
            fprintf(stderr, "epoll_wait: timeout\n");
        } else {
            if (event.events & EPOLLERR) {
                fprintf(stderr, "epoll_wait: EPOLLERR happens on fd %d\n", 
                    event.data.fd);
                err_cnt++;
            } else if (event.events & EPOLLHUP) {
                fprintf(stderr, "epoll_wait: EPOLLHUP happens on fd %d\n",
                    event.data.fd);
                err_cnt++;
            } else if (event.events & EPOLLIN) {
                err = read(event.data.fd, buf, sizeof(buf));
                fprintf(stderr, "epoll_wait: read fd %d, size %d\n",
                    event.data.fd, err);
            } else {
                fprintf(stderr, "epoll_wait: event %d\n", event.events);
                sleep(1);
            }
        }
        if (err_cnt >= 5) {
            break;
        }
    }
    err = 0;

__ret:
    if (epfd > 0) {
        close(epfd);
    }
    if (pipefd[0] > 0) {
        close(pipefd[0]);
    }
    if (pipefd[1] > 0) {
        close(pipefd[1]);
    }
    return err;
}
