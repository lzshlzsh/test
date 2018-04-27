/**
 * @file string_cow.cpp
 * @brief
 * @version 1.0
 * @date 06/27/2016 05:50:29 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
 
constexpr int fibonacci(const int n) {
//  if(n == 1) return 1;
//  if(n == 2) return 1;
  return fibonacci(n-1)+fibonacci(n-2);
}

template<typename T, typename U>
auto add(T x, U y) -> decltype(x+y) {
  return x+y;
}

int main()
{
  string str1 = "hello world";
  string str2 = str1;
  string str3;

  str3.assign(str1.data(), str1.length());

  printf ("Sharing the memory:\n");
  printf ("ststr1's address: %p\n", str1.c_str() );
  printf ("ststr2's address: %p\n", str2.c_str() );
  printf ("ststr3's address: %p\n", str3.c_str() );

  str2[1]='w';

  printf ("After Copy-On-Write:\n");
  printf ("ststr1's address: %p\n", str1.c_str() );
  printf ("ststr2's address: %p\n", str2.c_str() );
  printf ("ststr3's address: %p\n", str3.c_str() );

  std::cout << "add: " << add(1, 2.0) << std::endl;

  return 0;
}

