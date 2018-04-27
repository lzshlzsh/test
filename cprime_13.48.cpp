/**
* @file cprime_13.48.cpp
* @brief
* @version 1.0
* @date 04/27/2018 12:55:40 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <unistd.h>

#include <vector>
#include <iostream>

namespace {
int g_id = 1;
}

/**
 * @brief 
 * @class String
 */
class String
{
 public:
  /**
   * @brief
   */
  String(): id_(g_id++) {
    std::cout << __LINE__ << ':' << __FUNCTION__ 
        << " id:" << id_ << std::endl;
  }
  String(const String &str): id_(g_id++) {
    std::cout << __LINE__ << ':' << __FUNCTION__ 
        << " id:" << id_ 
        << " from id:" << str.id_ << std::endl;
  }

  String(String &&str) noexcept: id_(g_id++) {
    std::cout << __LINE__ << ':' << __FUNCTION__ 
        << " id:" << id_ 
        << " from id:" << str.id_ << std::endl;
  }

  String &operator =(const String &str) {
    std::cout << __LINE__ << ':' << __FUNCTION__ 
        << " id:" << id_ 
        << " from id:" << str.id_ << std::endl;
    return *this;
  }
  ~String() {
    std::cout << __LINE__ << ':' << __FUNCTION__ 
        << " id:" << id_ << std::endl;
  }
 protected:
 private:
  int id_;
};

int main() {
  std::vector<String> vstr;
  String str;

  for (int i=0; i<8; ++i) {
    vstr.push_back(str);
    std::cout << "--------" << std::endl;
  }

  return 0;
}

