//: C10:NamespaceOverriding1.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
#include <iostream>
#include "NamespaceMath.h"
int main() {
	using namespace Int;
  Integer a(-1); // Hides Math::a;
  using namespace Math;
  std::cout << a.getSign() << std::endl;
  a.setSign(negative);
  // Now scope resolution is necessary
  // to select Math::a :
  Math::a.setSign(positive);
} ///:~
