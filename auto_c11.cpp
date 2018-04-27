/**
* @file auto_c11.cpp
* @brief
* @version 1.0
* @date 02/05/2018 01:18:29 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/

#include <vector>
#include <iostream>

struct A {
  A(int _i, int _j): i(_i), j(_j) {}

  uint64_t i;
  uint64_t j;
};

int main() {
  std::vector<A> v;
  int k = 0;

  for (int i = 0; i < 10; ++i) {
    v.push_back(A{i, i});
  }

  for(auto &i: v) {
    k += i.i;
    k += i.j;
    i.i = 10;
    i.j = 11;
  }

  for(auto &i: v) {
    std::cout << i.i << ' ' << i.j << std::endl;
  }

  return 0;
}

