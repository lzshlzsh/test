/**
* @file cprime_16.42.cpp
* @brief
* @version 1.0
* @date 04/27/2018 03:22:44 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/

#include <iostream>
#include <vector>

template <typename T>
void g(T &&val) {
  std::cout << typeid(T).name() << std::endl;
  std::vector<T> vec;
}

template <typename T>
void h(const T &val) {
  std::cout << typeid(T).name() << std::endl;
  std::vector<T> vec;
}


int main() {
  int i = 0;
  const int ci = i;

//  g(i); // T = int &
//  g(ci); // T = const int &
  g(i * ci);
//  g(i=ci); // T = int &

  h(i);
  h(ci);
  h(i*ci);
  return 0;
}

