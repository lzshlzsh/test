/**
* @file std_bind.cpp
* @brief
* @version 1.0
* @date 11/16/2017 04:28:59 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/
#include <functional>

namespace {
/**
 * @brief 
 * @class Test
 */
class Test
{
 public:
  Test() {
    using namespace std::placeholders;
    foo_ = std::bind(&Test::foo, this, _1, _2);
  }
 protected:
  typedef std::function<int(int, int)> Foo;
  Foo foo_;

  int foo(int a, int b) {
    return a * b;
  }
 private:
};

}

int main() {
  Test t;

  return 0;
}
