/**
 * @file rvalue4.cpp
 * @brief
 * @version 1.0
 * @date 04/12/2018 08:03:31 PM
 * @author sammieliu,sammieliu@tencent.com
 * @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
 */

#include <iostream>
#include <utility>

void reference(int& v) {
	std::cout << "左值引用" << std::endl;
}
void reference(int&& v) {
	std::cout << "右值引用" << std::endl;
}
template <typename T>
void pass(T&& v) {
  v = 10;
	std::cout << "普通传参:";
	reference(v);
	std::cout << "std::move 传参:";
	reference(std::move(v));
	std::cout << "std::forward 传参:";
	reference(std::forward<T>(v));
}

template <typename T>
constexpr T &&g(typename std::remove_reference<T>::type &t) noexcept {
  return static_cast<T &&>(t);
}

template <typename T>
constexpr T &&g(typename std::remove_reference<T>::type &&t) noexcept {
  return static_cast<T &&>(t);
}

int main() {
	std::cout << "传递右值:" << std::endl;
	pass(1); // T = int

	std::cout << "传递左值:" << std::endl;
	int v = 1;
	pass(v); // T = T &

	std::cout << "传递右值引用:" << std::endl;
//  int tmp = 2;
  int &&vv = 2;
  pass(std::move(vv)); // T = int

  g<int>(v);
  g<int>(1);

	return 0;
}

