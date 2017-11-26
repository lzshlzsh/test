/**
* @file temp_object.cpp
* @brief
* @version 1.0
* @date 08/07/2017 11:37:03 AM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

namespace {

/**
* @brief 
* @class StringRef
*/
class StringRef
{
public:
  explicit
  StringRef(const char *data, const size_t len): data_(data), len_(len) {
    std::cout << "construct StringRef: " << to_string() << std::endl;
  }
  explicit
  StringRef(const std::string &str): StringRef(str.data(), str.length()) {}

  ~StringRef() {
    std::cout << "destruct StringRef: " << to_string() << std::endl;
  }
  const std::string to_string() const {
    return boost::lexical_cast<std::string>(static_cast<const void *>(data_)) +
      ":" + boost::lexical_cast<std::string>(len_);
  }
protected:
private:
  const char *data_;
  const size_t len_;
};

const StringRef foo() {
  StringRef str_ref(NULL, 1);
  return str_ref;
}


/**
 * @brief 
 * @class Test
 */
class Test
{
public:
  void set(const StringRef &str_ref) {
    std::cout << "Test::set" << std::endl;
  }
  void show() {
    std::cout << "Test::show" << std::endl;
  }
protected:
private:
};


}

int main() {
  Test test;

  const StringRef &str_ref = foo();
  std::cout << "str_ref: " << str_ref.to_string() << std::endl;

  test.set(StringRef(boost::lexical_cast<std::string>(123)));
  test.show();

  return 0;
}
