/**
* @file test_time_t.cpp
* @brief
* @version 1.0
* @date 07/13/2017 11:04:38 AM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/
#include <time.h>

#include <iostream>

int main() {
  time_t a = time(NULL);
  int d = 0x7fffffff;
  time_t b = time(NULL);

  if (a < b + static_cast<time_t>(d)) {
    std::cout << "a < .." << std::endl;
  } else {
    std::cout << "a > .." << std::endl;
  }

  return 0;
}

