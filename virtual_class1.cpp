/**
* @file virtual_class1.cpp
* @brief
* @version 1.0
* @date 05/25/2017 05:46:38 PM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/

#include <iostream>

/**
* @brief 
* @class Base
*/
class Base
{
public:
  /**
   * @brief
   */
  Base () {}

  virtual int foo() {
    std::cout << __LINE__ << std::endl;
    return 0;
  }
protected:
private:
};

/**
 * @brief 
 * @class SubClass
 */
class SubClass: public Base
{
public:
  /**
   * @brief
   */
  SubClass () {}
protected:
private:
  virtual int foo() {
    std::cout << __LINE__ << std::endl;
    return 0;
  }
};

int main() {
  SubClass sub;
  Base &b = sub;

  b.foo();

  return 0;
}
