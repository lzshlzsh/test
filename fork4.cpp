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
#include <sys/prctl.h>

#include <boost/thread/thread.hpp>

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

  err = prctl(PR_SET_PDEATHSIG, SIGKILL);
  if (err < 0) {
    perror("prctl");
    return -__LINE__;
  }

  err = setgid(100);
  if (-1 == err) {
    perror("setgid");
    return -__LINE__;
  }

  err = setuid(1003);
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

  int fd = open("/proc/1/ns/net", O_RDONLY);
  if (fd == -1) {
    perror("open");
  } else {
//    if (setns(fd, 0) == -1){
//      perror("setns");
//    }
  }

  execve(args.argv_[0], args.argv_, environ);
  return -__LINE__;
}


/**
 * @brief 
 * @class Thread
 */
class Thread
{
 public:
  Thread(int argc, char **argv): argc_(argc), argv_(argv) {
  }
  void operator() () {
    pid_t pid, child_tid;
    ThreadArgs args;

    args.argc_ = argc_ - 1;
    args.argv_ = &argv_[1];

#if 0
    // 该方法在tlinux系统中子进程会挂死在setgid
    pid = syscall(SYS_clone, 
                  CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD|CLONE_NEWNET,
                  0 /*child_stack*/,
                  NULL /*TID field in parent*/,
                  &child_tid /*TID field in child*/);
#else
    char *cstack = new char[128<<10];
    char *cstack_top = cstack + (128<<10);
    pid = clone(child, cstack_top, 
                CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD|CLONE_NEWNET,
                &args, NULL, NULL, &child_tid);
    delete []cstack;
#endif
    if (-1 == pid) {
      printf("clone failed\n");
      return;
    }/* else if (0 == pid) {
      printf("child start ...\n");
      exit(child(&args));
    } */
    printf("parent thead here..., child pid %d\n", pid);

    if (waitpid(pid, NULL, 0) == -1) {
      perror("waitpid");
      return;
    }

    printf("parent thead exit...\n");
  }
 protected:
 private:
  int argc_;
  char **argv_;
};


}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s exec_file [args]\n", argv[0]);
    return -__LINE__;
  }

  boost::thread t((Thread(argc, argv)));
  t.join();

  return 0;
}
