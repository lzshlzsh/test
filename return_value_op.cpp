/**
 * @file return_value_op.cpp
 * @brief
 * @version 1.0
 * @date 11/06/2015 11:26:32 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */
#include <iostream>

struct C {
  C() {}
  C(const C&) { std::cout << "A copy was made.\n"; }
};

C f() {
  return C();
}

C g(bool flag = false) {
    C c1, c2;
    return flag ? c1 : c2;
}

int main() {
  std::cout << "Hello World!\n";
  C obj = f();
  C obj2 = g();
  return 0;
}

