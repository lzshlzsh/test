/**
* @file stat.cpp
* @brief
* @version 1.0
* @date 10/15/2017 06:15:07 PM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "usage: " << argv[0] << " /proc/pid/fd/2" << std::endl;
    return -__LINE__;
  }
  struct stat stat_buf;
  if (stat(argv[1], &stat_buf)) {
    perror("stat");
    return -__LINE__;
  }
  if (S_ISSOCK(stat_buf.st_mode)) {
    std::cout << "is socket" << std::endl;
  } else {
    std::cout << stat_buf.st_mode << std::endl;
  }
  return 0;
}
