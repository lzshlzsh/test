/**
* @file rvalue5.cpp
* @brief
* @version 1.0
* @date 05/23/2018 03:49:42 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/

#include <string>
#include <unordered_map>
#include <iostream>

/**
 * @brief 
 * @class Test
 */
class Test
{
 public:
  /**
   * @brief
   */
  Test() {
    std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
        << std::endl;
  }

  Test(const char *str): str_(str) {
    std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
        << std::endl;
  }

  void set(const char *str) {
    str_ = str;
  }

  Test(Test &&test) noexcept: str_(std::move(test.str_)) {
    std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
        << std::endl;
  }
  Test &operator =(Test &&test) noexcept {
    std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
        << std::endl;
    str_ = std::move(test.str_);
    return *this;
  }

  ~Test() {
    std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
        << str_.length() << ':' << str_ << std::endl;
  }


  std::string str_;
 protected:
 private:
};

void foo(const std::string &str) {
  std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
      << str.length() << ':' << str << std::endl;
  std::string to_str(std::move(str));
  std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
      << str.length() << ':' << str << std::endl;
}

int main() {
  Test t1("123");
  Test t2;

  t2 = Test(std::move(t1));

  std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
      << t1.str_.length() << ':' << t1.str_ << std::endl;
  std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
      << t2.str_.length() << ':' << t2.str_ << std::endl;
  return 0;
////////////////////////////////////////////////////////////////////////////////
  std::unordered_map<int, Test> test_map;

  Test test("abcdef");
  std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
      << test.str_.length() << ':' << test.str_ << std::endl;
  test_map.insert(std::make_pair(0, std::move(test)));
//  test_map.insert(std::make_pair(0, test));
  std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
      << test.str_.length() << ':' << test.str_ << std::endl;

  test.set("afsafsafsd");
  std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
      << test.str_.length() << ':' << test.str_ << std::endl;
  test_map.emplace(1, std::move(test));
//  test_map.emplace(1, test);
  std::cout << __LINE__ << "\t" << __FUNCTION__ << "\t"
      << test.str_.length() << ':' << test.str_ << std::endl;

  foo("abcdef");

  return 0;
}

