/**
* @file test_inline_template.cpp
* @brief
* @version 1.0
* @date 11/02/2018 04:45:04 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <iostream>

namespace ns_a {

template <typename T>
  inline int foo(const T &&i) {
    std::cout << i << std::endl;
    return 0;
  }

inline int goo(const int i) {
  std::cout << i << std::endl;
  return 0;
}

} // namespace ns_a

namespace {

void test() {
  ns_a::foo(1);
//  foo(1);
  ns_a::goo(2);
}

} // namespace

int main() {
  test();
  return 0;
}
