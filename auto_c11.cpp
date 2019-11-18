/**
* @file auto_c11.cpp
* @brief
* @version 1.0
* @date 02/05/2018 01:18:29 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/

#include <vector>
#include <map>
#include <unordered_map>
#include <iostream>

namespace {

struct A {
  A(int _i, int _j): i(_i), j(_j) {}

  uint64_t i;
  uint64_t j;
};

template <typename T>
int test_map() {
  T m;
  for (auto i = 0; i < 10; ++i) {
    m.emplace(i, i); 
  }

  for (auto const &it: m) {
    std::cout << "delete " << it.first << std::endl;
    m.erase(it.first);
  }
  std::cout << m.size() << "****" << std::endl;
  return 0;
}

template <typename T>
int test_map2() {
  T m;
  for (auto i = 0; i < 10; ++i) {
    m.emplace(i, i); 
  }

  for (auto const &it: m) {
    std::cout << it.first << std::endl;
  }

  for (auto it = m.begin(); it != m.end();) {
    std::cout << "delete " << it->first << std::endl;
    it = m.erase(it);
  }

  std::cout << m.size() << "****" << std::endl;
  return 0;
}

} // namespace

int main() {
 
  test_map<std::map<int, int> >(); 
  test_map<std::unordered_map<int, int> >(); 
  test_map2<std::map<int, int> >(); 
  test_map2<std::unordered_map<int, int> >(); 

  return 0; 
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

