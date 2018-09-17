/**
* @file is_null_ptr.cpp
* @brief
* @version 1.0
* @date 08/30/2018 02:48:05 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <stdio.h>

class Secret;

char IsNullLiteralHelper(Secret* p); 

typedef char (&Ret)[2];
//char (&IsNullLiteralHelper(...))[2] {
Ret IsNullLiteralHelper(...) {
  static char a[2] = {'a', 'b'};
  return a;
}

int main() {
  printf("%ld, %ld\n", sizeof(IsNullLiteralHelper(0)),
         sizeof(IsNullLiteralHelper("abd")));
  return 0;
}

