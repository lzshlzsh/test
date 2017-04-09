#include <stdio.h>

#include "x.h"

int foo() {
  printf("[%s:%s:%d]%p\n", __FILE__, __FUNCTION__, __LINE__, &CONST);
  return 0;
}
