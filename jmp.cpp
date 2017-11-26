/**
* @file jmp.cpp
* @brief
* @version 1.0
* @date 10/11/2017 11:19:36 AM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/
#include <stdio.h>

void foo() {
  printf("in foo\n");
}

void *g_addr = reinterpret_cast<void*>(&foo);

int main()
{
  __asm__ __volatile__ (
      "jmp *%0\n"
      :
      :"m"(g_addr)
      );
  return 0;
}

