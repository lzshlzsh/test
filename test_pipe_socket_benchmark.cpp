/**
 * @file                test_pipe_socket_benchmark.cpp
 * @brief
 * @version             1.0
 * @date                2017年9月4日
 * @author              sarenlin(林钊航),sarenlin@tencent.com
 * @copyright           Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */


#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <map>

static uint64_t getCpuKhz() {
  FILE *fp = fopen("/proc/cpuinfo", "r");
  if (!fp)
    return 1;
  char buf[4096] = { 0 };
  fread(buf, 1, sizeof(buf), fp);
  fclose(fp);

  char *lp = strstr(buf, "cpu MHz");
  if (!lp)
    return 1;
  lp += strlen("cpu MHz");
  while (*lp == ' ' || *lp == '\t' || *lp == ':') {
    ++lp;
  }

  double mhz = atof(lp);
  uint64_t u = (uint64_t) (mhz * 1000);
  return u;
}

static uint64_t counter(void) {
  register uint32_t lo, hi;
  register uint64_t o;
  __asm__ __volatile__ (
      "rdtscp" : "=a"(lo), "=d"(hi)
  );
  o = hi;
  o <<= 32;
  return (o | lo);
}

static uint64_t GetTickMS() {
  static uint32_t khz = getCpuKhz();
  return counter() / khz;
}

int main(int argc, char **argv) {
  if (3 != argc) {
    std::cerr << "Usage : " << argv[0] << " type write_size" << std::endl;
    std::cerr << "type : 0  piep, 1 socket" << std::endl;
    return -1;
  }

  int fd[2];
  int rt;
  int type = atoi(argv[1]);
  if (0 == type) {
    rt = pipe2(fd, O_NONBLOCK);
  } else {
    rt = socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
  }

  char buff[65535];
  int write_size = atoi(argv[2]);
  pid_t pid;
  if (0 == (pid = fork())) {
    while (1) {
      std::map<int, int> res;
      uint64_t sum = 0;
      int fail_cnt;
      int write_cnt;
      int test_cnt = 1000000;
      while (test_cnt--) {
        uint64_t begin = GetTickMS();
        write(fd[1], buff, write_size);
        read(fd[0], buff, write_size);
        uint64_t end = GetTickMS();
        res[end - begin]++;
      }
      for (std::map<int, int>::iterator it = res.begin(); it != res.end();
          ++it) {
        std::cout << it->first << "\t" << it->second << std::endl;
      }
      std::cout << std::endl;
    }
  } else {
    uint64_t sum = 0;
    while (1) {
      read(fd[0], buff, write_size);
      write(fd[1], buff, write_size);
    }
  }
  return 0;
}



