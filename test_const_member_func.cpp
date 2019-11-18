/**
* @file test_const_member_func.cpp
* @brief
* @version 1.0
* @date 09/30/2018 10:22:25 AM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/


/**
 * @brief 
 * @class A
 */
class A
{
 public:
  /**
   * @brief
   */
  A() = default;


  void i(const int i) {
    i_ = i;
  }

 protected:
 private:
  int i_;
};


/**
 * @brief 
 * @class B
 */
class B
{
 public:
  /**
   * @brief
   */
  B() = default;
  void i(const int i) {
    a_.i(i);
  }
  void j(const int j) {
    j_ = j;
  }
 protected:
 private:
  int j_;
  A a_;
};

int main() {
  B b;
  b.i(0);
  b.j(0);
  return 0;
}

