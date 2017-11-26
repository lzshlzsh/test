/**
* @file const_string.cpp
* @brief
* @version 1.0
* @date 07/25/2017 12:14:56 PM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/

#include <iostream>

template <size_t N>
int foo(const char (&str)[N]) {
  std::cout << str << std::endl;
  return 0;
}

int main() {
//  const char *str = "ccccdddd";
  foo("aaabbbb");
//  foo(str); // Oops
  return 0;
}

