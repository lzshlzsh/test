/**
* @file inherit5.cpp
* @brief
* @version 1.0
* @date 08/09/2017 05:54:41 PM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/
#include <iostream>

/**
* @brief 
* @class Base1
*/
class Base1
{
public:
protected:
private:
};


/**
* @brief 
* @class Derived1
*/
class Derived1: public Base1
{
public:
protected:
private:
};

////////////////////////////////////////////////////////////////////////////////
/**
* @brief 
* @class Base2
*/
class Base2
{
public:
  virtual int init(const Base2 &base2, const Base1 &base1) const {
    std::cout << "Base2::init" << std::endl;
    return 0;
  }
protected:
private:
};

/**
 * @brief 
 * @class Derived2
 */
class Derived2: public Base2
{
public:
  virtual int init(const Derived2 &d2, const Derived1 &d1) const {
    std::cout << "Derived2::init" << std::endl;
    return 0;
  }
protected:
private:
};

int main() {
  Derived2 d2;
  Derived1 d1;

  const Base2 &b2 = Derived2();

  b2.init(d2, d1);

  return 0;
}
