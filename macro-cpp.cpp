/**
 * @file macro-cpp.cpp
 * @brief
 * @version 1.0
 * @date 11/06/2015 02:50:44 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include <stdio.h>

#include <iostream>

using namespace std;

#define A std::cout << __LINE__ << ":"
//#define A //
#define B(__fmt, __args...) printf(__fmt, ##__args)

#define STR1 "abc"
#define STR2 "efg"

/**
* @brief 
* @class TestClass
*/
class TestClass
{
public:
  enum {
    UID_TYPE_IMEI_IDFA = 3,
  };
  /**
   * @brief
   */
  TestClass () {}
protected:
private:
};

const char *str() {
    return STR1"/"STR2;
}

void test() {
    struct Test {
#define AAA 123
        Test() {
        cout << AAA << endl;
        }
    }t;

    cout << AAA << endl;

    cout << str() << endl;
}

int main(int argc, char **argv)
{
  printf("%d\n", TestClass::UID_TYPE_IMEI_IDFA);
  A << 123 << endl; 

  B("asdf\n");

  test();

  return 0;
}

