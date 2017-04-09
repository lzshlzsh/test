/*
 * =====================================================================================
 *
 *       Filename:  set-root-uid.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/01/2015 10:53:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */
#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define call(_func_) do { \
    errno = 0; \
    _func_; \
    perror(#_func_); \
} while (0)

static void print_resuid()
{
    uid_t uid, euid, suid;
    call(getresuid(&uid, &euid, &suid));
    printf("> uid %d, euid %d, suid %d\n", uid, euid, suid);
}

static void print_resgid()
{
    gid_t gid, egid, sgid;
    call(getresgid(&gid, &egid, &sgid));
    printf("> gid %d, egid, %d, sgid %d\n", gid, egid, sgid);
}

static void print_id()
{
    print_resuid();
    print_resgid();
    printf("\n\n");
}

int main(void) {
    print_id();

    call(setresuid(1001, 1000, 1001));
    print_id();

    call(setuid(1001));
    print_id();

    call(seteuid(1000));
    print_id();

    call(setuid(1000));
    print_id();

    return 0 ;       
}
