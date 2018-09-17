/**
* @file test_sstream.cpp
* @brief
* @version 1.0
* @date 09/17/2018 05:32:35 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/

#include <sstream>
#include <iostream>

int main() {
  std::stringstream ss;
  uint32_t k;
  uint64_t v;

  ss << "3763498804 31450996258";
 
  ss >> k >> v; 
  if (ss.fail()) {
    std::cout << "ss failed" << std::endl;
  } else {
    std::cout << k << " " << v << std::endl;
  }

  ss.clear();
  ss << "3763498 31450996258";
 
  ss >> k >> v; 
  if (ss.fail()) {
    std::cout << "ss failed" << std::endl;
  } else {
    std::cout << k << " " << v << std::endl;
  }

  return 0;
}

