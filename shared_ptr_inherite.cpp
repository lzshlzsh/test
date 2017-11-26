/**
* @file shared_ptr_inherite.cpp
* @brief
* @version 1.0
* @date 06/27/2017 05:39:48 PM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/

#include <iostream>

#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

/**
 * @brief 
 * @class Base
 */
class Base
{
public:
  int i_b_;

  Base(): i_b_(1) {}

  virtual ~Base() {}
protected:
private:
};


/**
 * @brief 
 * @class Derived
 */
class Derived: public Base
{
public:
  int i_d_;

  Derived(): i_d_(2) {}
protected:
private:
};

int main() {
  boost::shared_ptr<Base> base = boost::make_shared<Derived>();

  std::cout << base->i_b_ << std::endl;

  Derived *de = dynamic_cast<Derived *>(base.get());

  std::cout << de->i_d_ << std::endl;

  return 0;
}

