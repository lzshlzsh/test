/**
 * @file fork3.cpp
 * @brief
 * @version 1.0
 * @date 02/06/2017 12:30:00 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>

extern char **environ;

namespace {

/**
 * @brief 
 * @class ThreadArgs
 */
class ThreadArgs
{
public:
  int argc_;
  char **argv_;
protected:
private:
};

int child(void *arg) {
  ThreadArgs &args = *reinterpret_cast<ThreadArgs *>(arg);
  int err;
  uid_t ruid, euid, suid;
  gid_t rgid, egid, sgid;

  err = setgid(1000);
  if (-1 == err) {
    perror("setgid");
    return -__LINE__;
  }

  err = setuid(1000);
  if (-1 == err) {
    perror("setuid");
    return -__LINE__;
  }

  err = getresuid(&ruid, &euid, &suid);
  if (-1 == err) {
    perror("getresuid");
    return -__LINE__;
  }
  printf("ruid: %d, euid %d, suid %d\n", ruid, euid, suid);
  err = getresgid(&rgid, &egid, &sgid);
  if (-1 == err) {
    perror("getresgid");
    return -__LINE__;
  }
  printf("rgid: %d, egid %d, sgid %d\n", rgid, egid, sgid);
#if 0  
  int fd = open("/proc/1/ns/net", O_RDONLY);
  if (fd == -1) {
    perror("open");
    return -__LINE__;
  }

  if (setns(fd, 0) == -1){
    perror("setns");
    return -__LINE__;
  }
#endif

  execve(args.argv_[0], args.argv_, environ);
  return -__LINE__;
}

}

int main(int argc, char **argv)
{
  const int STACK_SIZE = (1 << 20);
  pid_t pid, child_tid;
  char *stack;
  char *stack_top;
  ThreadArgs args;

  if (argc < 2) {
    fprintf(stderr, "usage: %s exec_file [args]\n", argv[0]);
    return -__LINE__;
  }

  stack = reinterpret_cast<char *>(malloc(STACK_SIZE));
  stack_top = stack + STACK_SIZE;

  args.argc_ = argc - 1;
  args.argv_ = &argv[1];

//  pid = clone(child, stack_top,
//      CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD|CLONE_NEWNET,
//      &args, &pid, NULL, &child_tid);
  pid = syscall(SYS_clone, 
                CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD|CLONE_NEWNET,
                0 /*child_stack*/,
                NULL /*TID field in parent*/,
                &child_tid /*TID field in child*/);

  if (0 == pid) {
    exit(child(&args));
  }

  printf("parent thead here...\n");

  if (waitpid(pid, NULL, 0) == -1) {
    perror("waitpid");
    return -__LINE__;
  }

  printf("parent thead exit...\n");

  return 0;
}
